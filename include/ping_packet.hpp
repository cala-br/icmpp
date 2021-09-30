#ifndef PING_PACKET_HPP_
#define PING_PACKET_HPP_

#include "chrono_extension.hpp"
#include "icmp_packet.hpp"


namespace icmp::ping {
  struct PingPacket {
    packet::IcmpHeader header;
    uint16_t identifier;
    uint16_t sequenceNumber;
    int64_t timestamp;
    uint8_t data[26];

    static PingPacket echoRequest(uint16_t identifier);
    static PingPacket emptyEchoRequest();

  private:
    static thread_local inline uint16_t _seqNumber = 0;
  };
}

#endif // !PING_PACKET_HPP_
