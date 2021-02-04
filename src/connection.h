#ifndef CONNECTION_H_6E0A05012892400C8131B5B55A177A96
#define CONNECTION_H_6E0A05012892400C8131B5B55A177A96

#include "neuro_def.h"
#include "nerve.h"

namespace neuro {

struct connection {
  weight_t weight{0};
  nerve *out{nullptr};
  nerve *in{nullptr};
};

}

#endif //CONNECTION_H_6E0A05012892400C8131B5B55A177A96
