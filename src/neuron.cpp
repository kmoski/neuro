#include "neuron.h"
#include <cmath>

void neuro::neuron::process() {
  for(auto &conn : in_) {
    value += conn->weight * conn->in->value;
  }
  value = 1 / (1 + exp(-value));
}
void neuro::neuron::learn_head(const neuro::value_t &rate, const neuro::value_t &expected) {
  auto error = value - expected;
  learn_value = error * (value * (1 - value));
  for(auto &conn : in_) {
    conn->weight = conn->weight - conn->in->value * learn_value * rate;
  }
}
void neuro::neuron::learn(const neuro::value_t &rate) {
  value_t error{0};
  for(auto &conn : out_) {
    error += conn->weight * conn->out->learn_value;
  }
  learn_value = error * (value * (1 - value));
  for(auto &conn : in_) {
    conn->weight = conn->weight - conn->in->value * learn_value * rate;
  }
}
