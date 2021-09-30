#include "ping.hpp"


namespace icmp::ping {
  PingResult sendOne(EndPoint destination) {
    return sendOne(0, destination);
  }

  PingResult sendOne(uint16_t identifier, EndPoint destination) {
    return sendOne(PingPacket::echoRequest(identifier), destination);
  }

  PingResult sendOne(PingPacket packet, EndPoint destination) {
    return sendOne(IcmpSocket{}, packet, destination);
  }

  PingResult sendOne(IcmpSocket socket, EndPoint destination) {
    return sendOne(socket, PingPacket::echoRequest(0), destination);
  }

  PingResult sendOne(
    IcmpSocket socket,
    PingPacket packet,
    EndPoint destination
  ) {
    socket.send(packet, destination);
    auto received = socket.receive<PingPacket>();

    return {packet, received};
  }
}