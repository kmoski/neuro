#include <iostream>

#include "src/simple_builder.h"

using neuro::simple_builder;
using neuro::neuro_config;
using neuro::connection;
using neuro::neuron;
using neuro::weight_t;

using std::cout;
using std::endl;

weight_t rand_weight() {
  return -10 + rand() % 10;
}

weight_t rand_bi() {
  return rand() % 2;
}

weight_t nand(weight_t w1, weight_t w2) {
  return !((w1 > 0.5) & (w2 > 0.5));
}

int main() {
  vector<std::pair<uintptr_t, uintptr_t>> connections {
      {1, 3},
      {1, 4},
      {1, 5},
      {1, 6},
      {2, 3},
      {2, 4},
      {2, 5},
      {2, 6},
      {3, 7},
      {4, 7},
      {5, 7},
      {6, 7},
  };
  neuro_config cfg;
  cfg.in.push_back(1);
  cfg.in.push_back(2);
  cfg.out.push_back(7);
  connection *conn_p;
  for (auto &p : connections) {
    conn_p = new connection;
    conn_p->in = reinterpret_cast<neuron *>(p.first);
    conn_p->out = reinterpret_cast<neuron *>(p.second);
    conn_p->weight = rand_weight();
    cfg.net.push_back(conn_p);
  }

  auto *net = simple_builder::build(&cfg);

  for (int i(0); i < 100; ++i) {
    net->in.at(0)->value = rand_bi();
    net->in.at(1)->value = rand_bi();
    net->process();
    net->learn(0.01, nand(net->in.at(0)->value, net->in.at(1)->value));
  }
  auto w1 = rand_bi();
  auto w2 = rand_bi();
  cout << w1 << endl;
  cout << w2 << endl;
  net->process();
  cout << net->out.at(0)->value << endl;

  return 0;
}