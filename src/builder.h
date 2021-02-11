#ifndef BUILDER_H_E4BC7E7C821945779B7BA44065EF8C64
#define BUILDER_H_E4BC7E7C821945779B7BA44065EF8C64

#include <cstdint>
#include "net.h"

using std::uintptr_t;

namespace neuro {

struct neuro_config {
  vector<uintptr_t> in{};
  vector<uintptr_t> out{};
  vector<connection *> connections{};
};

class builder {
 public:
  static net *build(neuro_config *config);
};

}

#endif //BUILDER_H_E4BC7E7C821945779B7BA44065EF8C64
