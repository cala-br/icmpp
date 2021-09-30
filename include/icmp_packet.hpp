#ifndef ICMP_PACKET_HPP_
#define ICMP_PACKET_HPP_

#include <cstdint>
#include <array>
#include <concepts>
#include <memory>

namespace icmp {
  template <size_t Size>
  using NetworkBuffer = std::array<uint8_t, Size>;
}


namespace icmp::packet {
  constexpr auto IP_HEADER_SIZE = 20;

  struct IcmpHeader {
    uint8_t type;
    uint8_t code;
    uint16_t checksum;
  };

  template <typename Packet>
  concept IcmpPacket = requires(Packet p) {
    { p.header } -> std::convertible_to<IcmpHeader>;
  };


  template<IcmpPacket Packet, size_t Size = sizeof(Packet)>
  Packet *fromNetworkBuffer(NetworkBuffer<Size> &buffer) {
    return fromNetworkBuffer(buffer.data());
  }

  template<IcmpPacket Packet, size_t Size = sizeof(Packet)>
  Packet *fromNetworkBuffer(uint8_t *buffer) {
    return reinterpret_cast<Packet*>(buffer);
  }


  template<IcmpPacket Packet, size_t Size = sizeof(Packet)>
  NetworkBuffer<Size> toNetworkBuffer(Packet &packet) {
    auto result = NetworkBuffer<Size>{};
    auto buffer = reinterpret_cast<uint8_t*>(&packet);

    std::copy_n(buffer, Size, result.begin());
    return result;
  };


  template <IcmpPacket Packet, int SizeInWords = sizeof(Packet) / 2>
  uint16_t computeChecksum(Packet &packet) {
    auto buffer = reinterpret_cast<uint16_t*>(&packet);
    auto sum = 0ul;

    for (int i = 0; i < SizeInWords; i++) {
      sum += ntohs(buffer[i]);
    }
    
    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    return uint16_t(~sum);
  }
}

#endif // !ICMP_PACKET_HPP_
