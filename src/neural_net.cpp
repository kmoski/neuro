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
