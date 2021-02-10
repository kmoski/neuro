#include <map>
#include "simple_builder.h"

using std::map;

neuro::neuro_net *neuro::simple_builder::build(neuro::neuro_config *config) {
  // TODO(kmosk): check nullptr
  auto net = new neuro_net;
  map<uintptr_t, neuron *> neurons;
  for (auto &conn : config->net) {
    const auto &in = reinterpret_cast<uintptr_t>(conn->in);
    const auto &out = reinterpret_cast<uintptr_t>(conn->out);
    auto search_in = neurons.find(in);
    auto search_out = neurons.find(out);
    auto search_end = neurons.end();
    neuron *search_neuron;
    if (search_in == search_end) {
      search_neuron = new neuron;
      neurons[in] = search_neuron;
    } else {
      search_neuron = search_in->second;
    }
    search_neuron->out.push_back(conn);
    conn->in = search_neuron;
    if (search_out == search_end) {
      search_neuron = new neuron;
      neurons[out] = search_neuron;
    } else {
      search_neuron = search_out->second;
    }
    search_neuron->in.push_back(conn);
    conn->out = search_neuron;
  }
  for (auto &conn : config->in) {
    net->in.push_back(neurons.at(conn));
  }
  for (auto &conn : config->out) {
    net->out.push_back(neurons.at(conn));
  }
  for (auto &p : neurons) {  // bias neurons
    if (p.second->in.empty() && (std::find(config->in.begin(), config->in.end(), p.first) == config->in.end())) {
      p.second->value = 1;
    }
  }
  return net;
}
