#include <gtest/gtest.h>
#include "../../src/neural_net.h"

using namespace neuro;

/**
 * @brief test fixture for class neural_net
 */
class test_neural_net : public ::testing::Test {
 public:
  void SetUp() override {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)

    auto in_neuron_1 = new neuron;
    auto in_neuron_2 = new neuron;
    auto bias_neuron_3 = new neuron;
    auto hidden_neuron_4 = new neuron;
    auto hidden_neuron_5 = new neuron;
    auto hidden_neuron_6 = new neuron;
    auto bias_neuron_7 = new neuron;
    auto out_neuron_8 = new neuron;

    net.in.push_back(in_neuron_1);
    net.in.push_back(in_neuron_2);
    net.out.push_back(out_neuron_8);

    create_connection(in_neuron_1, hidden_neuron_4);
    create_connection(in_neuron_1, hidden_neuron_5);
    create_connection(in_neuron_1, hidden_neuron_6);
    create_connection(in_neuron_2, hidden_neuron_4);
    create_connection(in_neuron_2, hidden_neuron_5);
    create_connection(in_neuron_2, hidden_neuron_6);
    create_connection(bias_neuron_3, hidden_neuron_4, true);
    create_connection(bias_neuron_3, hidden_neuron_5, true);
    create_connection(bias_neuron_3, hidden_neuron_6, true);

    create_connection(hidden_neuron_4, out_neuron_8);
    create_connection(hidden_neuron_5, out_neuron_8);
    create_connection(hidden_neuron_6, out_neuron_8);
    create_connection(bias_neuron_7, out_neuron_8, true);
  };
  void TearDown() override {};

  /**
 * @brief generate random weight from -0.5 to 0.5
 * @param sampling - the number of discrete units in the computed area
 * @return random weight
 */
  static value_t rand_weight(const value_t &sampling) {
    auto random = rand(); // NOLINT(cert-msc50-cpp)
    return ((random % int(sampling)) / sampling) - 0.5;
  }

  /**
 * @brief generate random binary number
 * @return random binary number
 */
  static value_t rand_bi() {
    return rand() % 2; // NOLINT(cert-msc50-cpp)
  }

  /**
   * @brief create connection in heap and connect it into neurons
   * @param in input neuron
   * @param out output neuron
   * @param bias if true, then set input neuron value as 1
   */
  static void create_connection(neuron *in, neuron *out, bool bias = false) {
    auto conn = new connection;
    conn->weight = rand_weight(test_sampling);
    conn->in = in;
    conn->out = out;
    in->out.push_back(conn);
    out->in.push_back(conn);
    if (bias) {
      in->value = 1;
    }
  }

  static constexpr value_t test_sampling = 13; ///> sampling random weight
  static constexpr value_t min_mse = 0.001;  ///> minimal mean square error
  static constexpr value_t learning_rate = 0.1;  ///> neural net learning rate
  neural_net net;
};

/**
 * @test training connections for logic operation and
 */
TEST_F(test_neural_net, logic_and) {
  auto &in_a = net.in.at(0)->value;
  auto &in_b = net.in.at(1)->value;
  auto &out_c = net.out.at(0)->value;
  vector<value_t> expected;
  do {
    net.set_input({rand_bi(), rand_bi()});
    net.process();
    expected.clear();
    expected.push_back(value_t((in_a > 0.5) && (in_b > 0.5)));
    net.learn(learning_rate, expected);
  } while (net.mse(expected) > min_mse);
  net.set_input({1, 1});
  net.process();
  EXPECT_NEAR(out_c, 1, 0.5);
  net.set_input({1, 0});
  net.process();
  EXPECT_NEAR(out_c, 0, 0.5);
  net.set_input({0, 1});
  net.process();
  EXPECT_NEAR(out_c, 0, 0.5);
  net.set_input({0, 0});
  net.process();
  EXPECT_NEAR(out_c, 0, 0.5);
}

/**
 * @test training connections for logic operation or
 */
TEST_F(test_neural_net, logic_or) {
  auto &in_a = net.in.at(0)->value;
  auto &in_b = net.in.at(1)->value;
  auto &out_c = net.out.at(0)->value;
  vector<value_t> expected;
  do {
    net.set_input({rand_bi(), rand_bi()});
    net.process();
    expected.clear();
    expected = {value_t((in_a > 0.5) || (in_b > 0.5))};
    net.learn(learning_rate, expected);
  } while (net.mse(expected) > min_mse);
  net.set_input({1, 1});
  net.process();
  EXPECT_NEAR(out_c, 1, 0.5);
  net.set_input({1, 0});
  net.process();
  EXPECT_NEAR(out_c, 1, 0.5);
  net.set_input({0, 1});
  net.process();
  EXPECT_NEAR(out_c, 1, 0.5);
  net.set_input({0, 0});
  net.process();
  EXPECT_NEAR(out_c, 0, 0.5);
}

/**
 * @test training connections for logic operation xor
 */
TEST_F(test_neural_net, logic_xor) {
  auto &in_a = net.in.at(0)->value;
  auto &in_b = net.in.at(1)->value;
  auto &out_c = net.out.at(0)->value;
  vector<value_t> expected;
  do {
    net.set_input({rand_bi(), rand_bi()});
    net.process();
    expected.clear();
    expected.push_back(value_t((in_a > 0.5) ^ (in_b > 0.5)));
    net.learn(learning_rate, expected);
  } while (net.mse(expected) > min_mse);
  net.set_input({1, 1});
  net.process();
  EXPECT_NEAR(out_c, 0, 0.5);
  net.set_input({1, 0});
  net.process();
  EXPECT_NEAR(out_c, 1, 0.5);
  net.set_input({0, 1});
  net.process();
  EXPECT_NEAR(out_c, 1, 0.5);
  net.set_input({0, 0});
  net.process();
  EXPECT_NEAR(out_c, 0, 0.5);
}
