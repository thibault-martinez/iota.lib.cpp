#include <iostream>
#include <iota/iota>

static std::string proxy_host = "localhost";
static uint16_t    proxy_port = 14265;

const std::string&
get_proxy_host(void) {
  return proxy_host;
}

const uint16_t&
get_proxy_port(void) {
  return proxy_port;
}

int
main() {
  IOTA::API::Core api(get_proxy_host(), get_proxy_port());

  for (int i = 0; i < 1000; ++i) {
    api.getNodeInfo();
    api.addNeighbors({ "udp://8.8.8.8:14265", "udp://8.8.8.5:14265" });
  }
}
