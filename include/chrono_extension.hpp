#ifndef CHRONO_EXTENSION_HPP_
#define CHRONO_EXTENSION_HPP_

#include <cstdint>
#include <chrono>

namespace std::chrono {
  inline int64_t millisecondsSinceEpoch() {
    auto now = system_clock::now();
    auto duration = now.time_since_epoch();
    auto millis = duration_cast<milliseconds>(duration);
    return millis.count();
  }
}

#endif // !CHRONO_EXTENSION_HPP_
