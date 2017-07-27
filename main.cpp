#include "Extended.hpp"

#include "getBalancesRequest.hpp"
#include "getTrytesRequest.hpp"

int
main() {
  IOTA::API::Extended api;

  auto res = api.getTrytes(
      { "OAATQS9VQLSXCLDJVJJVYUGONXAXOFMJOZNSYWRZSWECMXAQQURHQBJNLD9IOFEPGZEPEMPXCIVRX9999" });
  std::cout << res.getTrytes()[0] << '\n';

  return 0;
}
