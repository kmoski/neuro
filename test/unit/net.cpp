#include <gtest/gtest.h>
#include "../../src/net.h"

using namespace neuro;
  // TODO(kmosk): write fixture
/**
 * @brief generate random weight from -0.5 to 0.5
 * @param sampling - the number of discrete units in the computed area
 * @return random weight
 */
value_t rand_weight(const value_t &sampling) {
  auto random = rand();
  return ((random % int(sampling)) / sampling) - 0.5;
}

/**
 * @brief generate random binary number
 * @return random binary number
 */
value_t rand_bi() {
  return rand() % 2;
}

/**
 * @test training connections for logic operation and
 */
TEST(net, logic_and) {
  net n;
  value_t sampling = 13;

  auto in_neuron_1 = new neuron;
  auto in_neuron_2 = new neuron;
  auto bias_neuron_3 = new neuron;

  auto hidden_neuron_4 = new neuron;
  auto hidden_neuron_5 = new neuron;
  auto hidden_neuron_6 = new neuron;
  auto bias_neuron_7 = new neuron;

  auto out_neuron_8 = new neuron;

  n.in.push_back(in_neuron_1);
  n.in.push_back(in_neuron_2);
  n.out.push_back(out_neuron_8);

  auto conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = in_neuron_1;
  conn->out = hidden_neuron_4;
  in_neuron_1->out.push_back(conn);
  hidden_neuron_4->in.push_back(conn);

  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = in_neuron_1;
  conn->out = hidden_neuron_5;
  in_neuron_1->out.push_back(conn);
  hidden_neuron_5->in.push_back(conn);

  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = in_neuron_1;
  conn->out = hidden_neuron_6;
  in_neuron_1->out.push_back(conn);
  hidden_neuron_6->in.push_back(conn);


  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = in_neuron_2;
  conn->out = hidden_neuron_4;
  in_neuron_2->out.push_back(conn);
  hidden_neuron_4->in.push_back(conn);

  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = in_neuron_2;
  conn->out = hidden_neuron_5;
  in_neuron_2->out.push_back(conn);
  hidden_neuron_5->in.push_back(conn);

  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = in_neuron_2;
  conn->out = hidden_neuron_6;
  in_neuron_2->out.push_back(conn);
  hidden_neuron_6->in.push_back(conn);


  bias_neuron_3->value = 1;

  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = bias_neuron_3;
  conn->out = hidden_neuron_4;
  bias_neuron_3->out.push_back(conn);
  hidden_neuron_4->in.push_back(conn);

  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = bias_neuron_3;
  conn->out = hidden_neuron_5;
  bias_neuron_3->out.push_back(conn);
  hidden_neuron_5->in.push_back(conn);

  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = bias_neuron_3;
  conn->out = hidden_neuron_6;
  bias_neuron_3->out.push_back(conn);
  hidden_neuron_6->in.push_back(conn);


  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = hidden_neuron_4;
  conn->out = out_neuron_8;
  hidden_neuron_4->out.push_back(conn);
  out_neuron_8->in.push_back(conn);


  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = hidden_neuron_5;
  conn->out = out_neuron_8;
  hidden_neuron_5->out.push_back(conn);
  out_neuron_8->in.push_back(conn);


  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = hidden_neuron_6;
  conn->out = out_neuron_8;
  hidden_neuron_6->out.push_back(conn);
  out_neuron_8->in.push_back(conn);


  bias_neuron_7->value = 1;
  conn = new connection;
  conn->weight = rand_weight(sampling);
  conn->in = bias_neuron_7;
  conn->out = out_neuron_8;
  bias_neuron_7->out.push_back(conn);
  out_neuron_8->in.push_back(conn);


}