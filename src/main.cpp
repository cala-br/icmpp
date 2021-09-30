#include <iostream>
#include "ping.hpp"

using namespace icmp;

int main() {
  auto ping = ping::sendOne({"8.8.8.8"});

  std::clog << ping.tripTimeMs << '\n';
}