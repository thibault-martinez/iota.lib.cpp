![IOTA Logo][iota-logo]

# IOTA C++ Library

[![Travis Build Status][travis-badge]][travis]
[![Appveyor Build Status][appveyor-badge]][appveyor]
[![Coveralls Status][coveralls-badge]][coveralls]
[![Codacy Status][codacy-badge]][codacy]
[![CodeFactor Status][codefactor-badge]][codefactor]
[![Documentation][documentation-badge]][documentation]
[![IOTA API coverage][iota-api-badge]][iota-api]
[![MIT License][license-badge]][license]

This is not (yet) an official C++ client library for the [IOTA Reference Implementation (IRI)](https://github.com/iotaledger/iri).

It implements both the [official API](https://iota.readme.io/docs/getting-started), as well as [newly proposed features](https://github.com/iotaledger/wiki/blob/master/api-proposal.md#proposed-api-calls).

## Table of Contents

1.  [Disclaimer](#disclaimer)
1.  [Documentation](#documentation)
    1.  [Installation](#installation)
    1.  [Getting Started](#getting-started)
    1.  [Doxygen](#doxygen)
    1.  [Wiki](#wiki)
    1.  [Examples](#examples)
1.  [Technologies & dependencies](#technologies--dependencies)
    1.  [Technologies](#technologies)
    1.  [Dependencies](#dependencies)
1.  [Community](#community)
    1.  [Resources](#resources)
    1.  [Contributing](#contributing)
    1.  [Donating](#donating)

## Disclaimer

-   This is an early beta release, expect unexpected results.
-   There may be performance and stability issues.
-   This library is still in early development and there may be breaking changes in the near future.
-   You may lose all your money.

## Documentation

### Installation

```
git clone --recursive git@github.com:thibault-martinez/iota.lib.cpp.git
cd iota.lib.cpp
mkdir build
cd build
cmake ..
make
```

### Getting Started

```cpp
IOTA::API::Core api("node.iotawallet.info", 14265);
auto            res = api.getTransactionsToApprove(27);

std::cout << res.getTrunkTransaction() << std::endl;
std::cout << res.getBranchTransaction() << std::endl;
```

### Doxygen

A [Doxygen documentation](https://thibault-martinez.github.io/iota.lib.cpp/html/) is available and provides full API documentation for the library.

### Wiki

A [Wiki](https://github.com/thibault-martinez/iota.lib.cpp/wiki) is available and provides full documentation for the library as well as [installation explanations](https://github.com/thibault-martinez/iota.lib.cpp/wiki/Installation).

### Examples

There's an extensive list of **test cases** on the [test folder](https://github.com/thibault-martinez/iota.lib.cpp/tree/master/test/source) that can be used as reference when developing apps with IOTA.

## Technologies & Dependencies

### Technologies

This library currently uses C++11.

### Dependencies

-   [C++ Requests](https://github.com/whoshuu/cpr)
-   [JSON For Modern C++](https://github.com/nlohmann/json)
-   [Keccak Code Package](https://github.com/gvanas/KeccakCodePackage)

## Community

### Resources

If you want to get involved in the community, need help with getting setup, have any issues related with the library or just want to discuss Blockchain, Distributed Ledgers and IoT with other people, feel free to visit one of our resources :

-   [Website](https://iota.org/)
-   [Discord](https://discordapp.com/invite/fNGZXvh)
-   [Forum](https://forum.iota.org/)
-   [Stack Exchange](https://iota.stackexchange.com/)

### Contributing

Please report any issues using the [Issue Tracker](https://github.com/thibault-martinez/iota.lib.cpp/issues).

### Donating

OZCTDHTFCB9PTAZWGYCGOA9XKDKPSHWVSZDJKZCOINNQTPNNEANGPBBDLSNGKDGCAAKBDVBOVCPTRLHTANMIRGFFGD

[iota-logo]: https://raw.githubusercontent.com/iotaledger/documentation/master/source/images/iota-logo.png

[travis]: https://travis-ci.org/thibault-martinez/iota.lib.cpp
[travis-badge]: https://travis-ci.org/thibault-martinez/iota.lib.cpp.svg?branch=master

[appveyor]: https://ci.appveyor.com/project/thibault-martinez/iota-lib-cpp/branch/master
[appveyor-badge]: https://ci.appveyor.com/api/projects/status/lp9awde5sykw16u0/branch/master?svg=true

[coveralls]: https://coveralls.io/github/thibault-martinez/iota.lib.cpp?branch=master
[coveralls-badge]: https://coveralls.io/repos/github/thibault-martinez/iota.lib.cpp/badge.svg?branch=master

[codacy]:
https://www.codacy.com/app/thibault.martinez.30/iota.lib.cpp?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=thibault-martinez/iota.lib.cpp&amp;utm_campaign=Badge_Grade
[codacy-badge]:
https://api.codacy.com/project/badge/Grade/a7c3070bcf4f4bc2bfff8f266208634a

[codefactor]:
https://www.codefactor.io/repository/github/thibault-martinez/iota.lib.cpp
[codefactor-badge]:
https://www.codefactor.io/repository/github/thibault-martinez/iota.lib.cpp/badge

[documentation]: https://thibault-martinez.github.io/iota.lib.cpp/html/
[documentation-badge]: https://img.shields.io/readthedocs/pip/stable.svg

[iota-api]:
https://iota.readme.io/reference
[iota-api-badge]:
https://img.shields.io/badge/IOTA%20API%20coverage-15/15%20commands-green.svg

[license]: https://github.com/thibault-martinez/iota.lib.cpp/blob/master/LICENSE
[license-badge]:
https://img.shields.io/apm/l/vim-mode.svg
