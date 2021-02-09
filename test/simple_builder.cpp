#include <gtest/gtest.h>
#include "../src/simple_builder.h"

using neuro::simple_builder;
using neuro::neuro_config;
using neuro::connection;
using neuro::neuron;
using neuro::weight_t;

/**
 * \test TODO
 */
TEST(simple_builder, get_null) {
  /*   3
   * 1 4
   *     7
   * 2 5
   *   6
   */
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
  weight_t i{0};
  for (auto &p : connections) {
    conn_p = new connection;
    conn_p->in = reinterpret_cast<neuron *>(p.first);
    conn_p->out = reinterpret_cast<neuron *>(p.second);
    conn_p->weight = i++;
    cfg.net.push_back(conn_p);
  }
  auto *net = simple_builder::build(&cfg);
  EXPECT_EQ(net->in.size(), 2);
  EXPECT_EQ(net->in.at(0)->in.size(), 0);
  EXPECT_EQ(net->in.at(0)->out.size(), 4);
  EXPECT_EQ(net->in.at(1)->in.size(), 0);
  EXPECT_EQ(net->in.at(1)->out.size(), 4);
  EXPECT_EQ(net->out.size(), 1);
  EXPECT_EQ(net->out.at(0)->out.size(), 0);
  EXPECT_EQ(net->out.at(0)->in.size(), 4);

  EXPECT_EQ(net->in.at(1)->out.at(3)->out->out.at(0)->weight, net->out.at(0)->in.at(3)->weight);
}

