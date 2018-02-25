//
// MIT License
//
// Copyright (c) 2017-2018 Thibault Martinez and Simon Ninon
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//

#include <gtest/gtest.h>

#include <iota/constants.hpp>
#include <iota/errors/illegal_state.hpp>
#include <iota/models/address.hpp>
#include <test/utils/constants.hpp>
#include <test/utils/expect_exception.hpp>

TEST(Address, FromCtor) {
  IOTA::Models::Address addrEmptyCtor;
  EXPECT_EQ(addrEmptyCtor.empty(), true);
  EXPECT_EQ(addrEmptyCtor.toTrytes(), "");
  EXPECT_EQ(addrEmptyCtor.toTrytesWithChecksum(), "");
  EXPECT_EQ(addrEmptyCtor.getChecksum(), "");
  EXPECT_EQ(addrEmptyCtor.getSecurity(), 2);
  EXPECT_EQ(addrEmptyCtor.getKeyIndex(), 0);
  EXPECT_EQ(addrEmptyCtor.getBalance(), 0);

  IOTA::Models::Address addrFullValidAddr(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(addrFullValidAddr.empty(), false);
  EXPECT_EQ(addrFullValidAddr.toTrytes(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(addrFullValidAddr.toTrytesWithChecksum(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(addrFullValidAddr.getChecksum(), ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));
  EXPECT_EQ(addrFullValidAddr.getSecurity(), 2);
  EXPECT_EQ(addrFullValidAddr.getKeyIndex(), 0);
  EXPECT_EQ(addrFullValidAddr.getBalance(), 0);

  IOTA::Models::Address addrValidAddrWithoutChecksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(addrValidAddrWithoutChecksum.empty(), false);
  EXPECT_EQ(addrValidAddrWithoutChecksum.toTrytes(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(addrValidAddrWithoutChecksum.toTrytesWithChecksum(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(addrValidAddrWithoutChecksum.getChecksum(),
            ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));
  EXPECT_EQ(addrValidAddrWithoutChecksum.getSecurity(), 2);
  EXPECT_EQ(addrValidAddrWithoutChecksum.getKeyIndex(), 0);
  EXPECT_EQ(addrValidAddrWithoutChecksum.getBalance(), 0);

  EXPECT_EXCEPTION(IOTA::Models::Address addrTooLongAddr(ACCOUNT_1_ADDRESS_1_HASH + '9'),
                   IOTA::Errors::IllegalState, "address has invalid length");

  EXPECT_EXCEPTION(
      IOTA::Models::Address addrInvalid(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM + "888888888"),
      IOTA::Errors::IllegalState, "address is not a valid trytes string");
}

TEST(Address, FullCtor) {
  IOTA::Models::Address addr = { "", 1, 2, 3 };
  EXPECT_EQ(addr.empty(), true);
  EXPECT_EQ(addr.toTrytes(), "");
  EXPECT_EQ(addr.toTrytesWithChecksum(), "");
  EXPECT_EQ(addr.getChecksum(), "");
  EXPECT_EQ(addr.getSecurity(), 3);
  EXPECT_EQ(addr.getKeyIndex(), 2);
  EXPECT_EQ(addr.getBalance(), 1);

  EXPECT_EXCEPTION(IOTA::Models::Address addrInvalidSecurity("", 1, 3, 5),
                   IOTA::Errors::IllegalState, "Invalid Security Level");
}

TEST(Transaction, SecurityGetterAndSetter) {
  IOTA::Models::Address addr = { "", 1, 2, 3 };
  EXPECT_EQ(addr.getSecurity(), 3);

  addr.setSecurity(1);
  EXPECT_EQ(addr.getSecurity(), 1);

  EXPECT_EXCEPTION(addr.setSecurity(5), IOTA::Errors::IllegalState, "Invalid Security Level");
}

TEST(Transaction, BalanceGetterAndSetter) {
  IOTA::Models::Address addr = { "", 1, 2, 3 };
  EXPECT_EQ(addr.getBalance(), 1);

  addr.setBalance(3);
  EXPECT_EQ(addr.getBalance(), 3);
}

TEST(Transaction, keyIndexGetterAndSetter) {
  IOTA::Models::Address addr = { "", 1, 2, 3 };
  EXPECT_EQ(addr.getKeyIndex(), 2);

  addr.setKeyIndex(3);
  EXPECT_EQ(addr.getKeyIndex(), 3);
}

TEST(Address, FromSetter) {
  IOTA::Models::Address address;

  address.setAddress("");
  EXPECT_EQ(address.empty(), true);
  EXPECT_EQ(address.toTrytes(), "");
  EXPECT_EQ(address.toTrytesWithChecksum(), "");
  EXPECT_EQ(address.getChecksum(), "");

  address.setAddress(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(address.empty(), false);
  EXPECT_EQ(address.toTrytes(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(address.toTrytesWithChecksum(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(address.getChecksum(), ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));

  address.setAddress(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(address.empty(), false);
  EXPECT_EQ(address.toTrytes(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(address.toTrytesWithChecksum(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(address.getChecksum(), ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));

  EXPECT_EXCEPTION(address.setAddress(ACCOUNT_1_ADDRESS_1_HASH + '9'), IOTA::Errors::IllegalState,
                   "address has invalid length");
  //! keeps previous value
  EXPECT_EQ(address.empty(), false);
  EXPECT_EQ(address.toTrytes(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(address.toTrytesWithChecksum(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(address.getChecksum(), ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));

  EXPECT_EXCEPTION(address.setAddress(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM + "888888888"),
                   IOTA::Errors::IllegalState, "address is not a valid trytes string");
  //! keeps previous value
  EXPECT_EQ(address.empty(), false);
  EXPECT_EQ(address.toTrytes(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(address.toTrytesWithChecksum(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(address.getChecksum(), ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));
}

TEST(Address, ImplicitConversion) {
  std::string           addrStr = ACCOUNT_1_ADDRESS_1_HASH;
  IOTA::Models::Address address = addrStr;

  EXPECT_EQ(address.empty(), false);
  EXPECT_EQ(address.toTrytes(), ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(address.toTrytesWithChecksum(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(address.getChecksum(), ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));
}

TEST(Address, GetChecksum) {
  IOTA::Models::Address addrEmptyCtor;
  EXPECT_EQ(addrEmptyCtor.getChecksum(), "");
  EXPECT_EQ(addrEmptyCtor.getChecksum(true), "");

  IOTA::Models::Address addrFullValidAddr(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(addrFullValidAddr.getChecksum(), ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));
  EXPECT_EQ(addrFullValidAddr.getChecksum(true),
            ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));

  IOTA::Models::Address addrValidAddrWithoutChecksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(addrValidAddrWithoutChecksum.getChecksum(),
            ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));
  EXPECT_EQ(addrValidAddrWithoutChecksum.getChecksum(true),
            ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));

  IOTA::Models::Address addrValidAddrInvalidChecksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                     "999999999");
  EXPECT_EQ(addrValidAddrInvalidChecksum.getChecksum(), "999999999");
  EXPECT_EQ(addrValidAddrInvalidChecksum.getChecksum(true),
            ACCOUNT_1_ADDRESS_1_HASH.substr(IOTA::AddressLength));
}

TEST(Address, toTrytesWithChecksum) {
  IOTA::Models::Address addrEmptyCtor;
  EXPECT_EQ(addrEmptyCtor.toTrytesWithChecksum(), "");
  EXPECT_EQ(addrEmptyCtor.toTrytesWithChecksum(true), "");

  IOTA::Models::Address addrFullValidAddr(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(addrFullValidAddr.toTrytesWithChecksum(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(addrFullValidAddr.toTrytesWithChecksum(true), ACCOUNT_1_ADDRESS_1_HASH);

  IOTA::Models::Address addrValidAddrWithoutChecksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  EXPECT_EQ(addrValidAddrWithoutChecksum.toTrytesWithChecksum(), ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_EQ(addrValidAddrWithoutChecksum.toTrytesWithChecksum(true), ACCOUNT_1_ADDRESS_1_HASH);

  IOTA::Models::Address addrValidAddrInvalidChecksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                     "999999999");
  EXPECT_EQ(addrValidAddrInvalidChecksum.toTrytesWithChecksum(),
            ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM + "999999999");
  EXPECT_EQ(addrValidAddrInvalidChecksum.toTrytesWithChecksum(true), ACCOUNT_1_ADDRESS_1_HASH);
}

TEST(Address, OperatorEq) {
  IOTA::Models::Address lhs_eq_checksum(ACCOUNT_1_ADDRESS_1_HASH);
  IOTA::Models::Address rhs_eq_checksum(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_TRUE(lhs_eq_checksum == rhs_eq_checksum);

  IOTA::Models::Address lhs_eq_invalid_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  IOTA::Models::Address rhs_eq_invalid_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  EXPECT_TRUE(lhs_eq_invalid_checksum == rhs_eq_invalid_checksum);

  IOTA::Models::Address lhs_eq_different_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                  "AAAAAAAAA");
  IOTA::Models::Address rhs_eq_different_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                  "999999999");
  EXPECT_TRUE(lhs_eq_different_checksum == rhs_eq_different_checksum);

  IOTA::Models::Address lhs_eq_checksum_for_one(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  IOTA::Models::Address rhs_eq_checksum_for_one(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  EXPECT_TRUE(lhs_eq_checksum_for_one == rhs_eq_checksum_for_one);

  IOTA::Models::Address lhs_neq(ACCOUNT_1_ADDRESS_1_HASH);
  IOTA::Models::Address rhs_neq(ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_FALSE(lhs_neq == rhs_neq);
}

TEST(Address, OperatorNEq) {
  IOTA::Models::Address lhs_eq_checksum(ACCOUNT_1_ADDRESS_1_HASH);
  IOTA::Models::Address rhs_eq_checksum(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_FALSE(lhs_eq_checksum != rhs_eq_checksum);

  IOTA::Models::Address lhs_eq_invalid_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  IOTA::Models::Address rhs_eq_invalid_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  EXPECT_FALSE(lhs_eq_invalid_checksum != rhs_eq_invalid_checksum);

  IOTA::Models::Address lhs_eq_different_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                  "AAAAAAAAA");
  IOTA::Models::Address rhs_eq_different_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                  "999999999");
  EXPECT_FALSE(lhs_eq_different_checksum != rhs_eq_different_checksum);

  IOTA::Models::Address lhs_eq_checksum_for_one(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  IOTA::Models::Address rhs_eq_checksum_for_one(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  EXPECT_FALSE(lhs_eq_checksum_for_one != rhs_eq_checksum_for_one);

  IOTA::Models::Address lhs_neq(ACCOUNT_1_ADDRESS_1_HASH);
  IOTA::Models::Address rhs_neq(ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_TRUE(lhs_neq != rhs_neq);
}

TEST(Address, OperatorEqTrytes) {
  IOTA::Models::Address lhs_eq_checksum(ACCOUNT_1_ADDRESS_1_HASH);
  IOTA::Types::Trytes   rhs_eq_checksum(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_TRUE(lhs_eq_checksum == rhs_eq_checksum);

  IOTA::Models::Address lhs_eq_invalid_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  IOTA::Types::Trytes   rhs_eq_invalid_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                              "999999999");
  EXPECT_TRUE(lhs_eq_invalid_checksum == rhs_eq_invalid_checksum);

  IOTA::Models::Address lhs_eq_different_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                  "AAAAAAAAA");
  IOTA::Types::Trytes   rhs_eq_different_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  EXPECT_TRUE(lhs_eq_different_checksum == rhs_eq_different_checksum);

  IOTA::Models::Address lhs_eq_checksum_for_one(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  IOTA::Types::Trytes   rhs_eq_checksum_for_one(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                              "999999999");
  EXPECT_TRUE(lhs_eq_checksum_for_one == rhs_eq_checksum_for_one);

  IOTA::Models::Address lhs_neq(ACCOUNT_1_ADDRESS_1_HASH);
  IOTA::Types::Trytes   rhs_neq(ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_FALSE(lhs_neq == rhs_neq);
}

TEST(Address, OperatorNEqTrytes) {
  IOTA::Models::Address lhs_eq_checksum(ACCOUNT_1_ADDRESS_1_HASH);
  IOTA::Types::Trytes   rhs_eq_checksum(ACCOUNT_1_ADDRESS_1_HASH);
  EXPECT_FALSE(lhs_eq_checksum != rhs_eq_checksum);

  IOTA::Models::Address lhs_eq_invalid_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  IOTA::Types::Trytes   rhs_eq_invalid_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                              "999999999");
  EXPECT_FALSE(lhs_eq_invalid_checksum != rhs_eq_invalid_checksum);

  IOTA::Models::Address lhs_eq_different_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                  "AAAAAAAAA");
  IOTA::Types::Trytes   rhs_eq_different_checksum(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                                "999999999");
  EXPECT_FALSE(lhs_eq_different_checksum != rhs_eq_different_checksum);

  IOTA::Models::Address lhs_eq_checksum_for_one(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM);
  IOTA::Types::Trytes   rhs_eq_checksum_for_one(ACCOUNT_1_ADDRESS_1_HASH_WITHOUT_CHECKSUM +
                                              "999999999");
  EXPECT_FALSE(lhs_eq_checksum_for_one != rhs_eq_checksum_for_one);

  IOTA::Models::Address lhs_neq(ACCOUNT_1_ADDRESS_1_HASH);
  IOTA::Types::Trytes   rhs_neq(ACCOUNT_1_ADDRESS_2_HASH);
  EXPECT_TRUE(lhs_neq != rhs_neq);
}
