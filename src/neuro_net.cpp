#include <map>
#include "neuro_net.h"

using std::map;

const long neuro::neuro_net::num_proc_ = sysconf(_SC_NPROCESSORS_ONLN);
void neuro::neuro_net::process() {
  vector<neuron *> neurones = in;
  vector<neuron *> next;

  for (auto &current : neurones) {
    current->process();
    next.insert(next.end(), current->out.begin(), current->out.end());
  }
}
void neuro::neuro_net::learn(const neuro::value_t &rate, const neuro::value_t &expected) {

}
