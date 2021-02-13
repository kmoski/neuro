#ifndef NEURON_H_7998EAD204184E6689A5C9FEDD27D51F
#define NEURON_H_7998EAD204184E6689A5C9FEDD27D51F

#include <vector>

using std::vector;

namespace neuro {

typedef double value_t;

class neuron;

/**
 * @brief base struct for transporting NN
 */
struct connection {
  value_t weight{0};  ///> weight of connection
  neuron *out{nullptr};  ///> connected to
  neuron *in{nullptr};  ///> connected from
};

/**
 * @brief base struct for learning NN
 */
struct neuron {
  vector<connection *> in{};  ///> input connections
  vector<connection *> out{};  ///> output connections
  value_t value{0};  ///> computing value
  value_t delta{0};  ///> delta weight for learning
};

}

#endif //NEURON_H_7998EAD204184E6689A5C9FEDD27D51F
