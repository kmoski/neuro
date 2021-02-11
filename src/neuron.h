#ifndef NEURON_H_7998EAD204184E6689A5C9FEDD27D51F
#define NEURON_H_7998EAD204184E6689A5C9FEDD27D51F

#include <vector>
#include <cstdint>
#include "def.h"

using std::vector;

namespace neuro {

typedef uintptr_t neuron_id;

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
  void process();
  void learn_head(const value_t &rate, const value_t &expected);
  void learn(const value_t &rate);
};

}

#endif //NEURON_H_7998EAD204184E6689A5C9FEDD27D51F
