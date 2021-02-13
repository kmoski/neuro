#include "neural_net.h"

/**
 * @test prepare connections and building simple connections
 *   3
 * 1 4
 *     7
 * 2 5
 *   6
 */
TEST_F(test_neural_net_constructor, common_struct) {
  net_config cfg;
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
  build(&cfg);

  ASSERT_EQ(in_.size(), 2);
  ASSERT_EQ(in_.at(0)->in.size(), 0);
  ASSERT_EQ(in_.at(0)->out.size(), 4);
  ASSERT_EQ(in_.at(1)->in.size(), 0);
  ASSERT_EQ(in_.at(1)->out.size(), 4);

  ASSERT_EQ(out_.size(), 1);
  ASSERT_EQ(out_.at(0)->out.size(), 0);
  ASSERT_EQ(out_.at(0)->in.size(), 4);

  ASSERT_EQ(in_.at(1)->out.at(3)->out->out.at(0)->weight, out_.at(0)->in.at(3)->weight);
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
TEST_F(test_neural_net_constructor, bias) {
  net_config cfg;
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
  build(&cfg);

  ASSERT_EQ(out_.at(0)->in.at(4)->in->value, 1);
  ASSERT_EQ(in_.at(0)->out.at(0)->out->in.at(2)->in->value, 1);
}

/**
 * @test contain null
 *   3
 * 1 4
 *     0
 * 2 5
 *   6
 */
TEST_F(test_neural_net_constructor, null) {
  net_config cfg;
  create_cfg(&cfg,
             {1, 2},
             {0},
             {{1, 3},
              {1, 4},
              {1, 5},
              {1, 6},
              {2, 3},
              {2, 4},
              {2, 5},
              {2, 6},
              {3, 0},
              {4, 0},
              {5, 0},
              {6, 0}});
  ASSERT_ANY_THROW(build(&cfg));
}

/**
 * @test training connections for logic operation and
 */
TEST_F(test_neural_net_learning, logic_and) {
  learning([](value_t a, value_t b){return (a > 0.5) && (b > 0.5);});
  set_input({1, 1});
  process();
  EXPECT_NEAR(get_output().at(0), 1, 0.5);
  set_input({1, 0});
  process();
  EXPECT_NEAR(get_output().at(0), 0, 0.5);
  set_input({0, 1});
  process();
  EXPECT_NEAR(get_output().at(0), 0, 0.5);
  set_input({0, 0});
  process();
  EXPECT_NEAR(get_output().at(0), 0, 0.5);
}

/**
 * @test training connections for logic operation or
 */
TEST_F(test_neural_net_learning, logic_or) {
  learning([](value_t a, value_t b){return (a > 0.5) || (b > 0.5);});
  set_input({1, 1});
  process();
  EXPECT_NEAR(get_output().at(0), 1, 0.5);
  set_input({1, 0});
  process();
  EXPECT_NEAR(get_output().at(0), 1, 0.5);
  set_input({0, 1});
  process();
  EXPECT_NEAR(get_output().at(0), 1, 0.5);
  set_input({0, 0});
  process();
  EXPECT_NEAR(get_output().at(0), 0, 0.5);
}

/**
 * @test training connections for logic operation xor
 */
TEST_F(test_neural_net_learning, logic_xor) {
  learning([](value_t a, value_t b){return (a > 0.5) ^ (b > 0.5);});
  set_input({1, 1});
  process();
  EXPECT_NEAR(get_output().at(0), 0, 0.5);
  set_input({1, 0});
  process();
  EXPECT_NEAR(get_output().at(0), 1, 0.5);
  set_input({0, 1});
  process();
  EXPECT_NEAR(get_output().at(0), 1, 0.5);
  set_input({0, 0});
  process();
  EXPECT_NEAR(get_output().at(0), 0, 0.5);
}
