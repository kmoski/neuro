#include "src/builder.h"

using neuro::builder;
using neuro::neuro_config;
using neuro::connection;
using neuro::neuron;
using neuro::value_t;

#include <iostream>
using std::cout;
using std::endl;

/**
 * @brief generate random weight from -0.5 to 0.5
 * @param sampling - the number of discrete units in the computed area
 * @return random weight
 */
value_t rand_weight(value_t sampling) {
  auto random = rand();
  return ((random % int(sampling)) / sampling) - 0.5;
}

value_t rand_bi() {
  return rand() % 2;
}

value_t nand(value_t w1, value_t w2) {
  return !((w1 > 0.5) & (w2 > 0.5));
}

int main() {
  srand(time(nullptr));
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
      {8, 7},
      {9, 3},
      {9, 4},
      {9, 5},
      {9, 6},
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
    conn_p->weight = rand_weight(13);
    cfg.connections.push_back(conn_p);
  }

  auto *net = builder::build(&cfg);

  for (int i(0); i < 100000; ++i) {
    net->in.at(0)->value = rand_bi();
    net->in.at(1)->value = rand_bi();
    net->process();
    net->learn(0.1, {nand(net->in.at(0)->value, net->in.at(1)->value)});
  }
  value_t w1 = 1;
  value_t w2 = 1;
  cout << w1 << " !& " << w2 << " = ";
  net->in.at(0)->value = w1;
  net->in.at(1)->value = w2;
  net->process();
  cout << net->out.at(0)->value << " (" << nand(w1, w2) << ")" << endl;

  w1 = 1;
  w2 = 0;
  cout << w1 << " !& " << w2 << " = ";
  net->in.at(0)->value = w1;
  net->in.at(1)->value = w2;
  net->process();
  cout << net->out.at(0)->value << " (" << nand(w1, w2) << ")" << endl;

  w1 = 0;
  w2 = 1;
  cout << w1 << " !& " << w2 << " = ";
  net->in.at(0)->value = w1;
  net->in.at(1)->value = w2;
  net->process();
  cout << net->out.at(0)->value << " (" << nand(w1, w2) << ")" << endl;

  w1 = 0;
  w2 = 0;
  cout << w1 << " !& " << w2 << " = ";
  net->in.at(0)->value = w1;
  net->in.at(1)->value = w2;
  net->process();
  cout << net->out.at(0)->value << " (" << nand(w1, w2) << ")" << endl;
  return 0;
}
