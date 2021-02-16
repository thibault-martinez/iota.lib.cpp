# Changelog

## 1.3.0
| Type | Details |
|------|---------|
|Date|August 30th, 2018|
|Tag|[v1.3.0](https://github.com/thibault-martinez/iota.lib.cpp/releases/tag/v1.3.0)|
|Description|Multi-Sig 32 bits, latest IRI API support and minor improvements|
|Added|<ul><li>support connection to HTTPS nodes</li><li>Extended::isReattachable</li><li>Extended::isPromotable</li><li>Extended::promoteTransaction</li><li>Core::wereAddressesSpentFrom</li><li>Core::checkConsistency</li><li>MultiSig support</li><li>32 bits support</li></ul>|
|Changed|<ul><li>Fix 0 balance issue when calling getAccountData</li><li>Minor build improvements</li><li>Add tips parameter to getBalances</li><li>Support new references response for getBalances</li></ul>|
|Removed|-|
|Upgrading|<ul><li>Previous getBalances response format based on milestone is deprecated. Please use the new format based on references from now on.</li></ul>|


## 1.2.1
| Type | Details |
|------|---------|
|Date|April 2nd, 2018|
|Tag|[v1.2.1](https://github.com/thibault-martinez/iota.lib.cpp/releases/tag/v1.2.1)|
|Description|Bundle finalization security patch.|
|Added|-|
|Changed|Bundle finalization routine is now executed repeatedly until normalized bundle hash contains no 13 ('M').|
|Removed|-|
|Upgrading|-|


## 1.2.0
**DO NOT USE IN PRODUCTION !**

**1.2.1 will be released quickly to fix a security issue**

| Type | Details |
|------|---------|
|Date|March 29th, 2018|
|Tag|[v1.2.0](https://github.com/thibault-martinez/iota.lib.cpp/releases/tag/v1.2.0)|
|Description|Performance analysis and improvements.|
|Added|<ul><li>Tag Model</li><li>Address Model</li><li>Seed Model</li><li>Bigint Class</li></ul>|
|Changed|<ul><li>Keccak384 now works with pointers instead of vectors</li><li>Kerl now works with bytes instead of trits</li><li>Signing operations have been drastically optimized</li><li>Trytes, trits and bytes conversion optimizations</li><li>Improvement of some API calls</li></ul>|
|Removed|<ul><li>Sponge interface</li><li>Sponge factory</li></ul>|
|Upgrading|v1.2.0 brings extensive small changes to the API that leads to breaking changes.<ul><li>Many `Types::Trytes` params have been converted to `Models::Address`, `Models::Tag`, `Models::Seed` types. We tried to make this change as smooth as possible by using implicit conversion. However, depending on your implementation, this may break the compilation. Alternatively, some validity checks that were previously done in the Extended or Core functions have been moved to these models, meaning that some exceptions may be triggered at different locations. Keep in mind that `Models::Seed`, `Models::Tag` and `Models::Address` ensure a valid state at any time (invalid addresses, tags or seeds are rejected by an exception).</li><li>Some parameters of the Extended API have been moved (in terms of position, or moved to the new Address, Seed or Tag models), changed to optional or removed. This mostly impacts parameters related to seed and addresses security, as well as start and end offset.</li><li>Some Extended functions that were not standard (due to legacy code) have been removed to sanitize the API.</li></ul>The list of changes is too big to address all breaking changes here in a relevant way. Please refer to the updated Doxygen documentation. Keep in mind that even though you may have multiple breaking changes, these should be straightforward to fix and should not impact the overall logic of your program.|

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
