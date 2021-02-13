#include <cmath>
#include "neural_net.h"

using std::move;
using std::sort;

const long neuro::neural_net::num_proc_ = sysconf(_SC_NPROCESSORS_ONLN);
void neuro::neural_net::process() {
  vector<neuron *> currents = in;
  vector<neuron *> nexts;
  while (!currents.empty()) {
    for (auto &current : currents) {
      current->process();
      if (!current->out.empty()) {
        for (auto &next : current->out) {
          nexts.push_back(next->out);
        }
      }
    }
    sort(nexts.begin(), nexts.end());
    nexts.erase(std::unique(nexts.begin(), nexts.end()), nexts.end());
    currents.clear();
    currents.swap(nexts);
  }
}
void neuro::neural_net::learn(const neuro::value_t &rate, const std::vector<neuro::value_t> &expected) {
  vector<neuron *> currents = out;
  vector<neuron *> nexts;
  {
    auto out_size = out.size();
    for (typeof(out_size) i{0}; i < out_size; ++i) {
      auto &current = out.at(i);
      current->learn_head(rate, expected.at(i));
      if (!current->in.empty()) {
        for (auto &next : current->in) {
          nexts.push_back(next->in);
        }
      }
    }
    sort(nexts.begin(), nexts.end());
    nexts.erase(std::unique(nexts.begin(), nexts.end()), nexts.end());
    currents.clear();
    currents.swap(nexts);
  }
  while (!currents.empty()) {
    for (auto &current : currents) {
      current->learn(rate);
      if (!current->in.empty()) {
        for (auto &next : current->in) {
          nexts.push_back(next->in);
        }
      }
    }
    sort(nexts.begin(), nexts.end());
    nexts.erase(std::unique(nexts.begin(), nexts.end()), nexts.end());
    currents.clear();
    currents.swap(nexts);
  }
}
void neuro::neural_net::set_input(const vector<value_t> &expected) {
  auto size = in.size();
  for (typeof(size) i{0}; i < size; ++i) {
    in.at(i)->value = expected.at(i);
  }
}
neuro::value_t neuro::neural_net::mse(const vector<value_t> &expected) {
  value_t sum_of_squares{0};
  auto size = out.size();
  for (typeof(size) i{0}; i < size; ++i) {
    sum_of_squares = pow(out.at(i)->value - expected.at(i), 2);
  }
  return sum_of_squares / value_t(size);
}
vector<neuro::value_t> neuro::neural_net::get_output() {
  vector<value_t> ret;
  for (auto &output : out) {
    ret.push_back(output->value);
  }
  return move(ret);
}
