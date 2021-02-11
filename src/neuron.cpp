#include "neuron.h"
#include <cmath>

void neuro::neuron::process() {
  if (!in.empty()) {
    value = 0;
    for (auto &conn : in) {
      value += conn->weight * conn->in->value;
    }
    value = 1 / (1 + exp(-value));
  }
}
void neuro::neuron::learn_head(const neuro::value_t &rate, const neuro::value_t &expected) {
  delta = (expected - value) * (value * (1 - value));
  for (auto &conn : in) {
    conn->weight = conn->weight + (rate * delta * conn->in->value);
  }
}
void neuro::neuron::learn(const neuro::value_t &rate) {
  if (!in.empty()) {
    value_t error{0};
    for (auto &conn : out) {
      error += conn->weight * conn->out->delta;
    }
    delta = error * (value * (1 - value));
    for (auto &conn : in) {
      conn->weight = conn->weight + (rate * delta * conn->in->value);
    }
  }
}
