#ifndef END_POINT_HPP_
#define END_POINT_HPP_

#include <arpa/inet.h>
#include "ip_address.hpp"

namespace icmp {
  class EndPoint {
  public:
    EndPoint(IPAddress address)
      : EndPoint(address, 0)
    {}
    
    EndPoint(IPAddress address, uint32_t port) {
      remote.sin_addr.s_addr = address.value;
      remote.sin_family = AF_INET;
      remote.sin_port = htons(port);
    }


    sockaddr *get() {
      return (sockaddr*)&getRemote();
    }

    sockaddr_in &getRemote() {
      return remote;
    }

    socklen_t size() {
      return sizeof(remote);
    }

  private:
    sockaddr_in remote;
  };
}

#endif // !END_POINT_HPP_
