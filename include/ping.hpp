#ifndef PING_HPP_
#define PING_HPP_

#include "icmp_socket.hpp"
#include "ping_packet.hpp"
#include "ping_result.hpp"

namespace icmp::ping {
  PingResult sendOne(EndPoint destination);
  PingResult sendOne(uint16_t identifier, EndPoint destination);
  PingResult sendOne(PingPacket packet, EndPoint destination);
  PingResult sendOne(IcmpSocket socket, EndPoint destination);
  PingResult sendOne(IcmpSocket socket, PingPacket packet, EndPoint destination);
}

#endif // !PING_HPP_
