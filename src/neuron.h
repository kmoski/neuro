#ifndef NEURON_H_7998EAD204184E6689A5C9FEDD27D51F
#define NEURON_H_7998EAD204184E6689A5C9FEDD27D51F

#include <vector>
#include <cstdint>
#include "neuro_def.h"

using std::vector;

namespace neuro {

typedef uintptr_t neuron_id;

class neuron;

/**
 * @brief Base struct for transporting
 */
struct connection {
  weight_t weight{0};  ///> Weight of connection
  neuron *out{nullptr};  ///> Connected to
  neuron *in{nullptr};  ///> Connected from
};

/**
 * @brief Base struct for computing
 */
struct neuron {
  vector<connection *> in{};  ///> Input connections
  vector<connection *> out{};  ///> Output connections
  value_t value{0};  ///> Computing value
  value_t delta{0};  ///> Delta weight for learning
  neuron_id id();
  void process();
  void learn_head(const value_t &rate, const value_t &expected);
  void learn(const value_t &rate);
};

}

#endif //NEURON_H_7998EAD204184E6689A5C9FEDD27D51F
