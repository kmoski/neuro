#include "neuron.h"
#include <cmath>

neuro::neuron_id neuro::neuron::id() {
  return reinterpret_cast<uintptr_t>(this);
}
void neuro::neuron::process() {
  for (auto &conn : in) {
    value += conn->weight * conn->in->value;
  }
  value = 1 / (1 + exp(-value));
}
void neuro::neuron::learn_head(const neuro::value_t &rate, const neuro::value_t &expected) {
  auto error = value - expected;
  delta = error * (value * (1 - value));
  for (auto &conn : in) {
    conn->weight = conn->weight - conn->in->value * delta * rate;
  }
}
void neuro::neuron::learn(const neuro::value_t &rate) {
  value_t error{0};
  for (auto &conn : out) {
    error += conn->weight * conn->out->delta;
  }
  delta = error * (value * (1 - value));
  for (auto &conn : in) {
    conn->weight = conn->weight - conn->in->value * delta * rate;
  }
}