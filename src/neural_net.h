#ifndef NEURAL_NET_H_AA95F39400E2461FA380529F9623080D
#define NEURAL_NET_H_AA95F39400E2461FA380529F9623080D

// Unix
#include <unistd.h>

#include <vector>
#include "neuron.h"

using std::vector;

namespace neuro {

class neural_net {
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
  void set_input(const vector<value_t> &expected);
  vector<value_t> get_output();
  void learn(const value_t &rate, const vector<value_t> &expected);
  value_t mse(const vector<value_t> &expected);
};

}

#endif //NEURAL_NET_H_AA95F39400E2461FA380529F9623080D
