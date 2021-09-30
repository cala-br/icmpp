#ifndef PING_RESULT_HPP_
#define PING_RESULT_HPP_

#include "chrono_extension.hpp"
#include "ping_packet.hpp"

namespace icmp::ping {
  struct PingResult {
    PingResult(PingPacket sent, PingPacket received):
      tripTimeMs(
        std::chrono::millisecondsSinceEpoch() - sent.timestamp
      )
    {}

    const int64_t tripTimeMs;
  };
}

#endif // !PING_RESULT_HPP_
