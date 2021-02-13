#ifndef NEURAL_NET_H_5AF9332667624294A9EEB4462C0E867D
#define NEURAL_NET_H_5AF9332667624294A9EEB4462C0E867D

#include <functional>
#include <gtest/gtest.h>
#include "../../src/neural_net.h"

using namespace neuro;
using std::function;

/**
 * @brief test fixture for building NN
 */
class test_neural_net_constructor :
    public ::testing::Test,
    public neural_net {
 public:
  void SetUp() override {};
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
   * @brief generate config struct for builder
   * @param cfg - pointer to config struct
   * @param in - ids of input neurones
   * @param out - ids of output neurones
   * @param connections - all connections in NN
   */
  static void create_cfg(net_config *cfg,
                         const vector<uintptr_t> &in,
                         const vector<uintptr_t> &out,
                         const vector<std::pair<uintptr_t, uintptr_t>> &connections) {
    cfg->in.insert(cfg->in.end(),
                   (reinterpret_cast<const vector<neuron *> *>(&in))->begin(),
                   (reinterpret_cast<const vector<neuron *> *>(&in))->end());
    cfg->out.insert(cfg->out.end(),
                    (reinterpret_cast<const vector<neuron *> *>(&out))->begin(),
                    (reinterpret_cast<const vector<neuron *> *>(&out))->end());
    auto size = connections.size();
    for (typeof(size) i{0}; i < size; ++i) {
      auto &p = connections.at(i);
      auto conn_p = new connection;
      conn_p->in = reinterpret_cast<neuron *>(p.first);
      conn_p->out = reinterpret_cast<neuron *>(p.second);
      conn_p->weight = rand_weight(test_sampling);
      cfg->connections.push_back(conn_p);
    }
  }
  static constexpr value_t test_sampling = 13; ///> sampling random weight
};

/**
 * @brief test fixture for learning NN
 */
class test_neural_net_learning :
    public test_neural_net_constructor {
 public:
  /**
 * @brief generate random binary number
 * @return random binary number
 */
  static value_t rand_bi() {
    return rand() % 2; // NOLINT(cert-msc50-cpp)
  }

  void SetUp() override {
    srand(time(nullptr)); // NOLINT(cert-msc51-cpp)
    net_config cfg;
    create_cfg(&cfg,
               {1, 2},
               {8},
               {{1, 4},
                {1, 5},
                {1, 6},
                {2, 4},
                {2, 5},
                {2, 6},
                {4, 8},
                {5, 8},
                {6, 8},
                {7, 8}});
    build(&cfg);
  };
  void TearDown() override {};

  /**
   * @brief learning NN while mse bigger than min_mse
   * @param logic_func function for learning NN
   */
  void learning(const function<value_t(value_t, value_t)> &logic_func) {
    vector<value_t> expected;
    do {
      set_input({rand_bi(), rand_bi()});
      process();
      expected.clear();
      auto input = get_input();
      expected.push_back(logic_func(input.at(0), input.at(1)));
    } while (learn(learning_rate, expected) > min_mse);
  }

  static constexpr value_t min_mse = 0.001;  ///> minimal mean square error
  static constexpr value_t learning_rate = 0.1;  ///> NN learning rate
};

#endif //NEURAL_NET_H_5AF9332667624294A9EEB4462C0E867D
