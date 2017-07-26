#include "Extended.hpp"

int
main() {
  IOTA::API::Extended api;

  auto res = api.getNodeInfo();

  return 0;
}
