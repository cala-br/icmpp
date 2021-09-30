#ifndef ICMP_SOCKET_HPP_
#define ICMP_SOCKET_HPP_

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string_view>
#include <array>
#include <linux/ip.h>

#include <bitset>

#include "end_point.hpp"
#include "icmp_packet.hpp"


namespace icmp {
  class IcmpSocket {
  public:
    IcmpSocket():
      client(
        socket(AF_INET, SOCK_RAW, IPPROTO_ICMP)
      )
    {}

    
    bool wasInstantiated() {
      return client >= 0;
    }


    template <packet::IcmpPacket Packet>
    bool send(Packet packet, EndPoint endPoint) {
      auto buffer = packet::toNetworkBuffer(packet);
      auto result =
        ::sendto(client, buffer.data(), buffer.size(), 0, endPoint.get(), endPoint.size());

      return result >= 0;
    }


    template <packet::IcmpPacket Packet, size_t Bytes = sizeof(Packet)>
    Packet receive() {
      using namespace icmp::packet;

      auto toRead = IP_HEADER_SIZE + Bytes;
      uint8_t buffer[toRead];
      ::read(client, buffer, toRead);
      
      return *fromNetworkBuffer<Packet>(buffer + IP_HEADER_SIZE);
    }

  private:
    int client;
  };
}

#endif // !ICMP_SOCKET_HPP_