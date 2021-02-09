#ifndef SIMPLE_BUILDER_H_E294F661C1BF493CB42F7DBC63CF8997
#define SIMPLE_BUILDER_H_E294F661C1BF493CB42F7DBC63CF8997

#include <cstdint>
#include "neuro_net.h"

using std::uintptr_t;

namespace neuro {

struct neuro_config {
  vector<uintptr_t> in{};
  vector<uintptr_t> out{};
  vector<connection *> net{};
};

class simple_builder {
 public:
  static neuro_net *build(neuro_config *config);
};

}

#endif //SIMPLE_BUILDER_H_E294F661C1BF493CB42F7DBC63CF8997
