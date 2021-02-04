#ifndef NEURON_H_7998EAD204184E6689A5C9FEDD27D51F
#define NEURON_H_7998EAD204184E6689A5C9FEDD27D51F

#include <vector>
#include "neuro_def.h"
#include "nerve.h"
#include "connection.h"

using std::vector;

namespace neuro {

class neuron : public nerve {
  vector<connection *> in_{};
  vector<connection *> out_{};
 public:
  void process();
  void learn_head(const value_t &rate, const value_t &expected);
  void learn(const value_t &rate);
};

}

#endif //NEURON_H_7998EAD204184E6689A5C9FEDD27D51F
