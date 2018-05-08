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

#include <iota/api/extended.hpp>
#include <iota/constants.hpp>
#include <iota/crypto/multi_signing.hpp>
#include <iota/models/bundle.hpp>
#include <iota/models/seed.hpp>
#include <iota/models/transfer.hpp>
#include <iota/types/trinary.hpp>
#include <test/utils/configuration.hpp>
#include <test/utils/constants.hpp>

TEST(Multisigning, Basic) {
  // IOTA::Models::Address msa(IOTA::Models::Address::MULTISIG);
  // auto                  api = IOTA::API::Extended{ get_proxy_host(), get_proxy_port() };
  //
  // auto firstKey = IOTA::Crypto::MultiSigning::key(IOTA::Types::trytesToBytes(ACCOUNT_1_SEED), 0,
  // 3); auto firstDigest = IOTA::Crypto::MultiSigning::digests(firstKey); EXPECT_EQ(
  //     IOTA::Types::bytesToTrytes(firstDigest),
  //     "GU9ZRLULWQRZWNHBLUYGDNURQXUFPBULCL9IECYWSNNFLNSDRXTUUFVHWKAOBPQBWQABPQGS9HXEVGPFXFIEUIGGEZQK"
  //     "9NVQNNPUCJIP9UL9HFEHCQF9EUKOFBRDMXTYEVA9PTAQGQWTJSFSPNG9MVCN9WKAUPCMHCPROSOJXGRAVOVKBCLOSDCP"
  //     "EMZTZEASAOQVT9JSTATWUZRPBXQCRAPMWGKOXBRSGPMUWAYDPYRLUWALURC");
  //
  // auto secondKey =
  //     IOTA::Crypto::MultiSigning::key(IOTA::Types::trytesToBytes(ACCOUNT_2_SEED), 0, 3);
  // auto secondDigest = IOTA::Crypto::MultiSigning::digests(secondKey);
  // EXPECT_EQ(
  //     IOTA::Types::bytesToTrytes(secondDigest),
  //     "RBORTXIJFOBZZ9Z9UPMLKMFWFSNIPUDAYCAQOZNHKQ9XRZCZTCCWRJHXAXARSUXCPIHSIEYPPGFGHCADBR9YVOBNQNVE"
  //     "MVPPSRNZYFSGXSKAKCLYMKJRZJHXRUXUTAYS9YBNKHVVVOANLAMKPPGXSEWQZOVBFQPAZAGNXBMYIUGPDRJMVQGXFZAI"
  //     "APTLAMPW9BFEHTWEL9UIB9XHVEAGSFATCDYLYLHOAVPCKPNSVVJRGXOYZ9C");
  //
  // msa.absorbDigests(firstDigest);
  // msa.absorbDigests(secondDigest);
  // msa.finalize();
  //
  // // TODO add in constants.hpp
  // EXPECT_EQ(msa.toTrytes(),
  //           "IZRSJJABYOJ9ZGMIDQPEYLIORMSJBHLIYVBOCOYG9CKKCCJG99MDZYANLWQFEIBGUA9QJSXXKTACDHSSZ");
  //
  // EXPECT_TRUE(msa.validate({ firstDigest, secondDigest }));
  //
  // IOTA::Models::Transfer tf{ ACCOUNT_5_ADDRESS_1_HASH, 1, "", IOTA::EmptyTag };
  //
  // auto txs = api.initiateTransfer(msa, msa.toTrytes(), { tf });
  //
  // EXPECT_EQ(txs.size(), 8UL);
  //
  // IOTA::Models::Bundle bundle(txs);
  //
  // IOTA::Crypto::MultiSigning::addSignature(bundle, msa, firstKey);
  // IOTA::Crypto::MultiSigning::addSignature(bundle, msa, secondKey);
  //
  // EXPECT_TRUE(IOTA::Crypto::MultiSigning::validateSignatures(bundle, msa));
}
