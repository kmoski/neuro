#include <cmath>
#include <map>
#include "neural_net.h"

using std::move;
using std::sort;
using std::unique;
using std::map;

// Unix
#include <unistd.h>
/*
 * - Linux, Solaris, AIX, OS X >= 10.4:
 *
 * sysconf(_SC_NPROCESSORS_ONLN);
 * Или прочитать в /proc/cpuinfo (для LSB-совместимых дистрибутивов).
 *
 *
 * - FreeBSD, OS X/Darwin, NetBSD, OpenBSD и их *BSD-сородичи:
 *
 * int mib[4] = {CTL_HW, HW_AVAILCPU, 0, 0};
 * size_t len = sizeof(numCPU);
 * sysctl(mib, 2, &numCPU, &len, NULL, 0);
 * if (numCPU < 0) {
 *     mib[1] = HW_NCPU;
 *     sysctl(mib, 2, &numCPU, &len, NULL, 0);
 * }
 *
 *
 * - HPUX:
 *
 * mpctl(MPC_GETNUMSPUS, NULL, NULL)
 *
 *
 * - IRIX:
 *
 * sysconf(_SC_NPROC_ONLN)
 *
 *
 * - OS X >= 10.5 (на Objective-C):
 *
 * NSUInteger a = [[NSProcessInfo processInfo] processorCount];
 * NSUInteger b = [[NSProcessInfo processInfo] activeProcessorCount];
 *
 *
 * - Windows
 *
 * SYSTEM_INFO sysinfo;
 * GetSystemInfo(&sysinfo);
 *
 * numCPU = sysinfo.dwNumberOfProcessors;
 */
const auto num_proc = sysconf(_SC_NPROCESSORS_ONLN);  ///> number of processing units

neuro::neural_net::neural_net(neuro::net_config *config) {
  build(config);
}
void neuro::neural_net::build(net_config *config) {
  map<uintptr_t, neuron *> neurons;
  for (auto &cfg_conn : config->connections) {
    const auto &in_id = reinterpret_cast<uintptr_t>(cfg_conn->in);
    const auto &out_id = reinterpret_cast<uintptr_t>(cfg_conn->out);
    if ((cfg_conn->in == nullptr) || (cfg_conn->out == nullptr)) {
      for (auto &conn : connections_) {
        delete conn;
      }
      connections_.clear();
      for (auto &n : neurons_) {
        delete n;
      }
      neurons_.clear();
      throw std::exception();
    }
    auto new_conn = new connection;
    new_conn->weight = cfg_conn->weight;
    connections_.push_back(new_conn);

    auto search_in = neurons.find(in_id);
    auto search_out = neurons.find(out_id);
    auto search_end = neurons.end();
    neuron *search_neuron;

    if (search_in == search_end) {
      search_neuron = new neuron;
      neurons[in_id] = search_neuron;
    } else {
      search_neuron = search_in->second;
    }
    search_neuron->out.push_back(new_conn);
    new_conn->in = search_neuron;

    if (search_out == search_end) {
      search_neuron = new neuron;
      neurons[out_id] = search_neuron;
    } else {
      search_neuron = search_out->second;
    }
    search_neuron->in.push_back(new_conn);
    new_conn->out = search_neuron;
  }
  for (auto &n : config->in) {
    in_.push_back(neurons.at(reinterpret_cast<uintptr_t>(n)));
  }
  for (auto &n : config->out) {
    out_.push_back(neurons.at(reinterpret_cast<uintptr_t>(n)));
  }
  for (auto &p : neurons) {
    neurons_.push_back(p.second);
    if (p.second->in.empty() && (find(in_.begin(), in_.end(), p.second) == in_.end())) {
      p.second->value = 1;
    }
  }
}
neuro::neural_net::~neural_net() {
  for (auto &conn : connections_) {
    delete conn;
  }
  for (auto &n : neurons_) {
    delete n;
  }
}
void neuro::neural_net::process() {
  vector<neuron *> current_neurons = in_;
  vector<neuron *> next_neurons;
  while (!current_neurons.empty()) {
    for (auto &current_neuron : current_neurons) {
      process_(current_neuron);
      if (!current_neuron->out.empty()) {
        for (auto &next : current_neuron->out) {
          next_neurons.push_back(next->out);
        }
      }
    }
    sort(next_neurons.begin(), next_neurons.end());
    next_neurons.erase(std::unique(next_neurons.begin(), next_neurons.end()), next_neurons.end());
    current_neurons.clear();
    current_neurons.swap(next_neurons);
  }
}
neuro::value_t neuro::neural_net::learn(const neuro::value_t &rate, const std::vector<neuro::value_t> &expected) {
  value_t sum_of_squares{0};
  vector<neuron *> current_neurons = out_;
  vector<neuron *> next_neurons;

  auto size = out_.size();
  for (typeof(size) i{0}; i < size; ++i) {
    auto &out_neuron = out_.at(i);
    sum_of_squares = pow(out_neuron->value - expected.at(i), 2);
    learn_head_(out_neuron, rate, expected.at(i));
    if (!out_neuron->in.empty()) {
      for (auto &conn : out_neuron->in) {
        next_neurons.push_back(conn->in);
      }
    }
  }
  sort(next_neurons.begin(), next_neurons.end());
  next_neurons.erase(unique(next_neurons.begin(), next_neurons.end()), next_neurons.end());
  current_neurons.clear();
  current_neurons.swap(next_neurons);

  while (!current_neurons.empty()) {
    for (auto &current_neuron : current_neurons) {
      learn_(current_neuron, rate);
      if (!current_neuron->in.empty()) {
        for (auto &conn : current_neuron->in) {
          next_neurons.push_back(conn->in);
        }
      }
    }
    sort(next_neurons.begin(), next_neurons.end());
    next_neurons.erase(unique(next_neurons.begin(), next_neurons.end()), next_neurons.end());
    current_neurons.clear();
    current_neurons.swap(next_neurons);
  }
  return sum_of_squares / value_t(size);
}
void neuro::neural_net::set_input(const vector<value_t> &expected) {
  auto size = in_.size();
  for (typeof(size) i{0}; i < size; ++i) {
    in_.at(i)->value = expected.at(i);
  }
}
vector<neuro::value_t> neuro::neural_net::get_input()  const noexcept {
  vector<value_t> ret;
  for (auto &output : in_) {
    ret.push_back(output->value);
  }
  return move(ret);
}
vector<neuro::value_t> neuro::neural_net::get_output()  const noexcept {
  vector<value_t> ret;
  for (auto &output : out_) {
    ret.push_back(output->value);
  }
  return move(ret);
}
void neuro::neural_net::process_(neuro::neuron *n) {
  if (!n->in.empty()) {
    n->value = 0;
    for (auto &conn : n->in) {
      n->value += conn->weight * conn->in->value;
    }
    n->value = 1 / (1 + exp(-n->value));
  }
}
void neuro::neural_net::learn_head_(neuro::neuron *n, const neuro::value_t &rate, const neuro::value_t &expected) {
  n->delta = (expected - n->value) * (n->value * (1 - n->value));
  for (auto &conn : n->in) {
    conn->weight = conn->weight + (rate * n->delta * conn->in->value);
  }
}
void neuro::neural_net::learn_(neuro::neuron *n, const neuro::value_t &rate) {
  if (!n->in.empty()) {
    value_t error{0};
    for (auto &conn : n->out) {
      error += conn->weight * conn->out->delta;
    }
    n->delta = error * (n->value * (1 - n->value));
    for (auto &conn : n->in) {
      conn->weight = conn->weight + (rate * n->delta * conn->in->value);
    }
  }
}
