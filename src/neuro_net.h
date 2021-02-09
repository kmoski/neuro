#ifndef NEURO_NET_H_3EC071C551974630B38E639498C837F5
#define NEURO_NET_H_3EC071C551974630B38E639498C837F5

// Unix
#include <unistd.h>

#include <vector>
#include "neuron.h"

using std::vector;

namespace neuro {

class neuro_net {
  /*
   * - Linux, Solaris, AIX, OS X >= 10.4:
   *
   * sysconf(_SC_NPROCESSORS_ONLN);
   * Или прочитать в /proc/cpuinfo (для LSB-совместимых дистрибутивов).
   *
   *
   * - FreeBSD, OS X/Darwin, NetBSD, OpenBSD и их *BSD-сородичи:
   *
   * int mib[4] = {CTL_HW, HW_AVAILCPU, 0, 0};
   * size_t len = sizeof(numCPU);
   * sysctl(mib, 2, &numCPU, &len, NULL, 0);
   * if (numCPU < 0) {
   *     mib[1] = HW_NCPU;
   *     sysctl(mib, 2, &numCPU, &len, NULL, 0);
   * }
   *
   *
   * - HPUX:
   *
   * mpctl(MPC_GETNUMSPUS, NULL, NULL)
   *
   *
   * - IRIX:
   *
   * sysconf(_SC_NPROC_ONLN)
   *
   *
   * - OS X >= 10.5 (на Objective-C):
   *
   * NSUInteger a = [[NSProcessInfo processInfo] processorCount];
   * NSUInteger b = [[NSProcessInfo processInfo] activeProcessorCount];
   *
   *
   * - Windows
   *
   * SYSTEM_INFO sysinfo;
   * GetSystemInfo(&sysinfo);
   *
   * numCPU = sysinfo.dwNumberOfProcessors;
   */
  static const long num_proc_;  ///> Number of processor cores
 public:
  vector<neuron *> in{};
  vector<neuron *> out{};
  void process();
  void learn(const value_t &rate, const value_t &expected);
};

}

#endif //NEURO_NET_H_3EC071C551974630B38E639498C837F5
