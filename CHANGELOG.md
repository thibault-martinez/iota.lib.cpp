# Changelog

## 1.1.0
| Type | Details |
|------|---------|
|Date|February 17th, 2018|
|Tag|[v1.1.0](https://github.com/thibault-martinez/iota.lib.cpp/releases/tag/v1.1.0)|
|Description|Cross-Platform support, CI integration & buildchain improvement, little fixes & improvements|
|Added|<ul><li>Windows support since MSVC 2015</li><li>Appveyor CI integration for Windows builds</li><li>Additional platforms builds for mac & linux on Travis CI, including code inspection tools</li></ul>|
|Changed|<ul><li>Performance improvement of BigInt initialization (from trits)</li><li>Use the official Keccak repository as a submodule dependency rather than using a private copy of the source files.</li><li>Fix some overflow issues on 32bits systems for getBalances and prepareTransfers</li></ul>|
|Removed|<ul><li>Remove boost multiprecision as a dependency, which mean boost is no longer required to build this library</li></ul>|
|Upgrading|There is no breaking changes, upgrading from 1.0.0 to 1.1.0 should be smooth. Major changes are about windows support and boost dependency drop, that do not require any change on your side|

## 1.0.0
| Type | Details |
|------|---------|
|Date|February 1st, 2018|
|Tag|[v1.0.0](https://github.com/thibault-martinez/iota.lib.cpp/releases/tag/v1.0.0)|
|Description|This is the first stable release.<br/>There may be lots of changes since the alpha and the beta that are can unfortunately not be detailed here.<br/>Please refer to the latest wiki and doxygen documentation.|
|Added|-|
|Changed|-|
|Removed|-|
|Upgrading|-|
