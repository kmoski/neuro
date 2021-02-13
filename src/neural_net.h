#ifndef NEURAL_NET_H_AA95F39400E2461FA380529F9623080D
#define NEURAL_NET_H_AA95F39400E2461FA380529F9623080D

#include "neuron.h"

namespace neuro {

/**
 * @brief struct for building NN
 */
struct net_config {
  vector<neuron *> in{};  ///> input neuron IDs
  vector<neuron *> out{};  ///> output neuron IDs
  vector<connection *> connections{};  ///> connections in NN ()
};

/**
 * @brief todo
 */
class neural_net {
  static void process_(neuron *n);
  static void learn_head_(neuron *n, const value_t &rate, const value_t &expected);
  static void learn_(neuron *n, const value_t &rate);
 protected:
  neural_net() = default;
  vector<neuron *> in_{};
  vector<neuron *> out_{};
  vector<neuron *> neurons_{};
  vector<connection *> connections_{};
 public:
  explicit neural_net(net_config *config);
  ~neural_net();
  void build(net_config *config);
  void process();
  void set_input(const vector<value_t> &expected);
  vector<value_t> get_input() const noexcept; // NOLINT(modernize-use-nodiscard)
  vector<value_t> get_output() const noexcept; // NOLINT(modernize-use-nodiscard)
  value_t learn(const value_t &rate, const vector<value_t> &expected);
};

}

#endif //NEURAL_NET_H_AA95F39400E2461FA380529F9623080D
