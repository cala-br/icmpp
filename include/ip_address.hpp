#ifndef IP_ADDRESS_HPP_
#define IP_ADDRESS_HPP_

#include <arpa/inet.h>

namespace icmp {
  struct IPAddress {
    IPAddress(const char *address)
      : value(inet_addr(address))
    {}

    constexpr IPAddress(
      uint8_t o4,
      uint8_t o3,
      uint8_t o2,
      uint8_t o1
    ): 
      value( // basically htons(o4.o3.o2.o1)
        o1 << 24 | o2 << 16 | o3 << 8 | o4
      )
    {}

    const in_addr_t value;


    IPAddress operator=(const char *address) {
      return {address};
    }
  };
}

#endif // !IP_ADDRESS_HPP_
