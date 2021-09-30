#include <random>
#include "icmp_socket.hpp"
#include "ping_packet.hpp"


namespace icmp::ping {
  PingPacket PingPacket::echoRequest(uint16_t identifier) {
    auto packet = emptyEchoRequest();
    packet.identifier = htons(identifier);
    packet.header.checksum = htons(packet::computeChecksum(packet));

    return packet;
  }

  PingPacket PingPacket::emptyEchoRequest() {
    auto result = PingPacket{
      .header = {
        .type = 8,
        .code = 0,
        .checksum = 0,
      },
      .identifier = 0,
      .sequenceNumber = htons(++_seqNumber),
      .timestamp = std::chrono::millisecondsSinceEpoch(),
    };

    std::copy_n("abcdefghijklmnopqrstuvwxyz", sizeof(result.data), (char*)result.data);
    return result;
  }
}