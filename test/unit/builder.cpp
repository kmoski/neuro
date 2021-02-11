#include <gtest/gtest.h>
#include "../../src/builder.h"

using namespace neuro;

/**
 * @brief test fixture for class builder
 */
class test_builder : public ::testing::Test {
 public:
  void SetUp() override {};
  void TearDown() override {
    delete n;
  };
  /**
   * @brief generate config struct for builder
   * @param cfg - pointer to config struct
   * @param in - ids of input neurones
   * @param out - ids of output neurones
   * @param connections - all connections in neural net
   */
  static void create_cfg(neuro_config *cfg,
                         const vector<uintptr_t> &in,
                         const vector<uintptr_t> &out,
                         const vector<std::pair<uintptr_t, uintptr_t>> &connections) {
    cfg->in.insert(cfg->in.end(), in.begin(), in.end());
    cfg->out.insert(cfg->out.end(), out.begin(), out.end());
    auto size = connections.size();
    for (typeof(size) i{0}; i < size; ++i) {
      auto &p = connections.at(i);
      auto conn_p = new connection;
      conn_p->in = reinterpret_cast<neuron *>(p.first);
      conn_p->out = reinterpret_cast<neuron *>(p.second);
      conn_p->weight = i;
      cfg->connections.push_back(conn_p);
    }
  }
  net *n{nullptr};
};

/**
 * @test prepare connections and building simple connections
 *   3
 * 1 4
 *     7
 * 2 5
 *   6
 */
TEST_F(test_builder, common_struct) {
  neuro_config cfg;
  create_cfg(&cfg,
             {1, 2},
             {7},
             {{1, 3},
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
              {6, 7}});
  n = builder::build(&cfg);

  ASSERT_EQ(n->in.size(), 2);
  ASSERT_EQ(n->in.at(0)->in.size(), 0);
  ASSERT_EQ(n->in.at(0)->out.size(), 4);
  ASSERT_EQ(n->in.at(1)->in.size(), 0);
  ASSERT_EQ(n->in.at(1)->out.size(), 4);

  ASSERT_EQ(n->out.size(), 1);
  ASSERT_EQ(n->out.at(0)->out.size(), 0);
  ASSERT_EQ(n->out.at(0)->in.size(), 4);

  ASSERT_EQ(n->in.at(1)->out.at(3)->out->out.at(0)->weight, n->out.at(0)->in.at(3)->weight);
}

/**
 * @test containing bias neurons
 *   3
 * 1 4
 *     7
 * 2 5
 *   6
 * 9 8
 */
TEST_F(test_builder, bias) {
  neuro_config cfg;
  create_cfg(&cfg,
             {1, 2},
             {7},
             {{1, 3},
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
              {9, 6}});
  n = builder::build(&cfg);

  ASSERT_EQ(n->out.at(0)->in.at(4)->in->value, 1);
  ASSERT_EQ(n->in.at(0)->out.at(0)->out->in.at(2)->in->value, 1);
}
