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

#include <iota/models/bundle.hpp>
#include <test/utils/constants.hpp>

TEST(Bundle, CtorDefault) {
  IOTA::Models::Bundle b;

  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{});
}

TEST(Bundle, CtorFull) {
  IOTA::Models::Bundle b({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 } });

  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{ IOTA::Models::Transaction(
                                     ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0) });
}

TEST(Bundle, ConstGetters) {
  const IOTA::Models::Bundle b({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 } });

  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{ IOTA::Models::Transaction(
                                     ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0) });
}

TEST(Bundle, TransactionsGetterAndSetter) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{});

  b.addTransaction({ ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 });
  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{ IOTA::Models::Transaction(
                                     ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0) });
}

TEST(Bundle, TransactionsGetterAndSetterEmplace) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{});

  b.addTransaction({ ACCOUNT_1_ADDRESS_1_HASH, 42, "TAG", 21 }, 3);
  EXPECT_EQ(b.getTransactions(),
            std::vector<IOTA::Models::Transaction>(
                { IOTA::Models::Transaction(ACCOUNT_1_ADDRESS_1_HASH, 42, "TAG", 21),
                  IOTA::Models::Transaction(ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0),
                  IOTA::Models::Transaction(ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0) }));
}

TEST(Bundle, TransactionsNonConstGetter) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{});

  auto& trx = b.getTransactions();
  trx.push_back({ ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 });

  EXPECT_EQ(b.getTransactions(), std::vector<IOTA::Models::Transaction>{ IOTA::Models::Transaction(
                                     ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0) });
}

TEST(Bundle, IsEmptyWithCtor) {
  IOTA::Models::Bundle b({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 } });
  EXPECT_EQ(b.empty(), false);
}

TEST(Bundle, IsEmptyWithDefaultCtor) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.empty(), true);
}

TEST(Bundle, IsEmptyWithAdd) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.empty(), true);

  b.addTransaction({ ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 });
  EXPECT_EQ(b.empty(), false);
}

TEST(Bundle, IsEmptyWithPush) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.empty(), true);

  auto& trx = b.getTransactions();
  trx.push_back({ ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 });
  EXPECT_EQ(b.empty(), false);
}

TEST(Bundle, GetLengthWithCtor) {
  IOTA::Models::Bundle b({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 } });
  EXPECT_EQ(b.getLength(), 1UL);
}

TEST(Bundle, GetLengthWithDefaultCtor) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getLength(), 0UL);
}

TEST(Bundle, GetLengthWithAdd) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getLength(), 0UL);

  b.addTransaction({ ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 });
  EXPECT_EQ(b.getLength(), 1UL);
}

TEST(Bundle, GetLengthWithPush) {
  IOTA::Models::Bundle b;
  EXPECT_EQ(b.getLength(), 0UL);

  auto& trx = b.getTransactions();
  trx.push_back({ ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 0 });
  EXPECT_EQ(b.getLength(), 1UL);
}

TEST(Bundle, EqOperator) {
  IOTA::Models::Bundle eq_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 2, 3, 4 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle eq_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 2, 10, 11 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });

  eq_lhs.getTransactions()[0].setBundle("eq");
  eq_rhs.getTransactions()[0].setBundle("eq");

  EXPECT_EQ(eq_lhs == eq_rhs, true);

  IOTA::Models::Bundle neq_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 2, 3, 4 },
                                 { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle neq_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 0, 10, 11 },
                                 { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });

  neq_lhs.getTransactions()[0].setBundle("eq");
  neq_rhs.getTransactions()[0].setBundle("neq");

  EXPECT_EQ(neq_lhs == neq_rhs, false);
}

TEST(Bundle, NeqOperator) {
  IOTA::Models::Bundle eq_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 2, 3, 4 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle eq_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 2, 10, 11 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });

  eq_lhs.getTransactions()[0].setBundle("eq");
  eq_rhs.getTransactions()[0].setBundle("eq");

  EXPECT_EQ(eq_lhs != eq_rhs, false);

  IOTA::Models::Bundle neq_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 2, 3, 4 },
                                 { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle neq_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 0, 10, 11 },
                                 { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });

  neq_lhs.getTransactions()[0].setBundle("eq");
  neq_rhs.getTransactions()[0].setBundle("neq");

  EXPECT_EQ(neq_lhs != neq_rhs, true);
}

TEST(Bundle, LtOperator) {
  IOTA::Models::Bundle eq_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 2, 3, 4 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle eq_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 2, 10, 11 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });
  EXPECT_EQ(eq_lhs < eq_rhs, false);

  IOTA::Models::Bundle lt_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 0, 3, 4 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle lt_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 2, 10, 11 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });
  EXPECT_EQ(lt_lhs < lt_rhs, true);

  IOTA::Models::Bundle gt_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 2, 3, 4 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle gt_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 0, 10, 11 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });
  EXPECT_EQ(gt_lhs < gt_rhs, false);
}

TEST(Bundle, GtOperator) {
  IOTA::Models::Bundle eq_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 2, 3, 4 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle eq_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 2, 10, 11 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });
  EXPECT_EQ(eq_lhs > eq_rhs, false);

  IOTA::Models::Bundle lt_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 0, 3, 4 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle lt_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 2, 10, 11 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });
  EXPECT_EQ(lt_lhs > lt_rhs, false);

  IOTA::Models::Bundle gt_lhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 1, 2, 3, 4 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 5, 6, 7, 8 } });
  IOTA::Models::Bundle gt_rhs({ { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 9, 0, 10, 11 },
                                { ACCOUNT_1_ADDRESS_1_HASH, 0, "TAG", 12, 13, 14, 16 } });
  EXPECT_EQ(gt_lhs > gt_rhs, true);
}

//!
//! Tests are based on real values (can be found on iota tangle explorer)
//! Input are valid transactions
//! Output is a valid bundle hash
//!

TEST(Bundle, Finalize) {
  IOTA::Models::Bundle b;

  b.addTransaction(
      { "RGGVEMTBJIZEES9AWZTCMIQPAKJZ9JYDZBZCWCUGQPFMHCMAUXNFRSHLIKELNPUYTIPMJQKDJQVORVHWWBFZQRYWGZ"
        "OVVRBJPOFDDJKHICAFQEWZH9XGLYZGPYNHOQMGCIOP9GLUTHPCEZHWRYAPOYLKRZLSAMXNLCAWSMCVBTJOUBPDJXZL"
        "MQKRW9HHTFOOFHZKE9SNXBNPLKNWXABPZFOSPDCZPXVHQRXYFWSUAGLIVJJQABUWKNZWPURHNQMVXBMWYWXKJBOWBD"
        "KHFMQNBSI9JWMMBRFAJJPGIVMOELGT9EPYLSODUMLCNWBIDWSRHVDFLYAPORAUUOESG9JTFXFDRFVIZMNUJFIKSJTR"
        "QRMTBTYKK9DGEGSZMVNRNBLWXJJUZHEHK9GNVSXEATUAOOBSTGKEVLGZBNROMZOUDVBEJYFCIDOCQMNJPIXMVFEB9O"
        "SYJGNNJACNQEFS9LITZENJUEFUMMONVPPLVOPISNIZNOILKTU9SGMWKBZLQVERKFAMJEOQQOTAVSJMTLY9JSWKFPFI"
        "HMRWMWZ9OWJKNKIIVGEMHAMLTQPRE9UQKZIPT9VXJTN9CGUGGNRBGNOVYBX9QPCHR9LNLIGSWREHDPNWAQP9TEOEKP"
        "ICMPDJQZCGPNSQERKOQJUJJDEQCQILQOOKFHJNDUJMDYZWLDTLUTYWHDLGGPHUVMOAJZRXWGXONTDEMIYVRCBJVDXH"
        "TGF9LRWHDDOHEVGQLWPXLPXMCYOZQBSFLNOEHBUORDUSBFYJPCLFSRKOTNMEUQCMYKHHRBJFNNWA9TSRXLPVYIAJOL"
        "PKAKIAJYXYSIUKYMEYTZXTBIUJBXEHIOBHANMNDYBCDSBQQSBYKAIEU9OXMIYRGGRXYYEGXB99STNHOQDPK9MCMZBL"
        "ZEMKCFOSOTVNULCHGTCIFTFFLXACQPUVPH9ADV9GUZZTPBJJYVUHKDLUUSAHWNZNGTRRUIAUKNHNIBNZRXBFRFEVNL"
        "KUYDUQUCKXOTVYTHCLGVGPTWX9ZHOSGEYLNGNOJUQPSDI9KNEYWIOSJPVTZMIK9FUUKRSYFQZJCZVWBACAWRCZZBCV"
        "CXQANNFHNIFZACTRBTIOHWTNTTFCACGDSMGZFDCBRYCYOMZXTKOCWATJRPRCIAWWHQIIOPLTTKISZXQJDYSCVEZCWG"
        "GXKKEBJAIHXPOYYCARKBSWMMKHVSXPHGWKNKQPEADI9CX9HCEVINXITKIOJVPBTGRJWDZI9LYDPXVLGTMBHNFIROHQ"
        "RRVNBBZVMNCCVGZW9OXHKQNLLPMTQGFEGLSYIOFJGXZ9SPYWIVZEZYIRAMROSWYZUIIUJVVPXVAONMOCYJJBKMQUO9"
        "OBBJXFNESYQXNWULUDSAWNBZOOGWQSUXZFMNRWCZGHT9KCIJPWYWXBNDYXGLGDDELQHYBFGVTTCJEIVYEJDCKRAECH"
        "CHPCGVSRJZJSDEATRIFOQXF9YMVQFSARZFQUGUSVKMUP9GNBTPRROTSZIEWXHPCBQYAUOXKFOZWDBKUFCKXNXMFZGV"
        "UEKCCLRWFBAKROVAVPNNRFYPEWBNXTWVGLZMOWAIEF9WOCGXZCVQXWFLUYAKFBRLABYUHNMBCAAFVADSPPOCKQXHTA"
        "KQLSOWPLFRVCNUQNNRLGKRFUARWJXGEABPIJWQX9TFQNPOSZZQPYDTNXDIBXVWQPYQDGPLXHXKQKGI9EAFQUFXMONE"
        "JXRFZMHJSDYBXHSBVBZCOZVNFQQKEISCOSYLWH9WTRSJYRBQJGUQQVBAUBNWYBIPZZQHMIUPHBTKIVXQ9DONMSWLRT"
        "EGWSUNSZWXWGUXG9YFXUHOKOJRMWNRXOYINKEJFZDOFENGSCFBJYNKBTZLDXYTPYYXYBWGZLATTFQYEDZRQMRROBGX"
        "HGGZXSCFR9SEDBQRMKXQXJETMJJMWGTUBBKARMZAUSENUCTRYOBTKISTSEPRPDXEPQ99HGAKOCXJN9PGKJVMMGITIU"
        "IIMFIQSYGIJ9I9JPVSPICRHPCXVRIZNTVQQSVTJZXEIHYXMOXDEFKDQBOEERRAWBRLNWUHJANYBXLIMOC9FNKUBXFC"
        "QXXPKOSMGPLZJHAYQV9LFNLVKSPGLIBPYACKKWHYIOFBUUJVEQQUJJFRSXWCTEVUNLKLMYGMSOCXCDAKSIOFKDWHQK"
        "OOCCHHYNTZLE99BQZ9VLCSML9RB",
        0, 1, "999999999999999999999999999999999999999999999999999999NFRPTDAX9XUSPAQBPVPFXF99EA9",
        "BIGFB9ABABLWWIRSYRDVFRVURZJLDCMOUGYYGNSKQ9JSLXGHXKZPCBMCEMFUIP9UMGRBIVVDQIHDZ9999",
        1507233573,
        "HYZJPVGLNYMHKMC9TRQXNXSSHZZUOUBZRJMLZETENPQKTIECOSG9CFLNVWNMSPXQGCHMTZT9OCR9A9999",
        "KTRETJZQNAZKOLFKJGQUYLSYVHTFJBE9MZCUOAWZXTFOHWMMZBPOFVGQCRSASCBKDQZRIXNILUZQ99999",
        "KPWCHICGJZXKE9GSUDXZYUAPLHAKAHYHDXNPHENTERYMMBQOPSQIDENXKLKCEYCPVTZQLEEJVYJZV9BWU", 0, "",
        "MNPL99999999999999999999999", 0, 0, 0 });

  b.addTransaction(
      { "BUZYVXO9XB99HAXGWEVDAAYDIUVINLZVQWGMGYMANUCVXFPQV9OAOBEPXBRYIKMUSGTCFZUSXTNNOELBBMRJ"
        "QXGLCYGUWBZVNOGPCLFJLMKIWXTTQBICGWJVHPLJWYJXUFUWRWMRWWZHCTXNYJFYTQNAWPSRYPI9LOPZRVFM"
        "ADJFQQ9BZUBKLMJLZSBSBFPWLUKJYZHTPCTJNALXTGSHHUZKNNIYREZOESRNFO9GFNPPNVUZ9KABTIYIALFI"
        "OLJYSUPQPFELKLZKBRZQXFEXIEGKZUMOAYCUQQOXELMOQJIFPCKDKVBJ9IZSTMBIPF9OMGXINNUFPVRNXLDC"
        "OQZOARW9DJFANYZXSZXMAWCOPHOY9XYCLNJRZRUHKHLPLHKWFPZWPSIWIWKZXZVSMGEIBSAULAGCSSVJZHNB"
        "THUCXIXXJPLFFE9ZEJPCLMIYKQCHTVRZPZELVGJAWMAHVDMUFKJHXLEWZWXQRYEPENVKPGMYNIGVQYJVQBYC"
        "PNDRSHYJV9HHKVCGKF99OZEBNLMQSPEJKPYDTYBUANSUMQDSCNGKKZKVSQFTO9LFKEUPWGAGYOJKTHPOAHJM"
        "RASHGDELFYSG9XDF9OYGMDYTCUMMOLUYMPC9FDPPKHLYZTMMFHZDPCWYBGMKVEOUXXOPN9RTQPOVETCHZHWG"
        "QZMADCXEVGTWXY9LBZBPYUMPQHOGWHRWK9XDOMDJAAZRSOOIYSWUVBXTVJWJBVNVPFEWEJZUJCKBEHBOGKZH"
        "ZE9COE9BDVGAMCJQDQZAFRWOFYXVUSIAJQSOC9SI9SEQGCKPGCXFXYSJNHTMHTXCRVYNPVSDYEUTHFYUAIKA"
        "PTMQLPXIGZHWO9BFZNOZC9VBJAVTJCUESQJDMBETBIZODVHZDSWQDOUIPCYTZCGOPMJJIDOTYPAMTTEXLVZ9"
        "CTARGVHAIQODWUHKEX9IDDD9HNBNYRVGI9LARZKMSTAJIHZWPPIAGTLFTPRAIJUFYYXTIJJZW9UEFJKQCKXW"
        "STKP9CSMXHCRCECZDBRHIABBIQEBYWNPFHXFFAYEOLDAHFOCVK9AAKF9EQLNFSDEORKFYXKUXSGSTQMBVRNI"
        "BOGUWYNJISWGTZRUBAUPSACRTWPAQIDXOXUXMKEVCDZLBUXWINABWYBDMZNIYNVPYLRKUULTMNNKZUFNQOQK"
        "ROJSXWYTBRDSJQKTOUXLMXVCVIXEYPZWBSMEXMBGUIVACRTGKDEIYZKP9KQCQXPWRXNLGQOATRHCXJFQINXF"
        "YQIDTPUJVXKUYVRYHWDHWSNLWUFPNNJZVNMRFWPZBJCRRSHMHUG9NKKH9SOXTUJUAXBF9MHYWHJ9ZTJRUQFK"
        "RLHMNVPWX9XFXLMVJAGASMWMIFYUZFAUCEIOOYMEYWOIZTNEWFVZKOQFECWEPSMOYFSJJKEJQMPSXGE9WTYR"
        "QJVMHUQZFD9MJUFFCNSGAZCTXYPIJFNSXAUCYPGZMNWMQWSWCKAQYKXJTWINSGPPZG9HLDLEAWUWEVCTVRCB"
        "DFOXKUROXH9HXXAXVPEJFRSLOGRVGYZASTEBAQNXJJROCYRTDPYFUIQJVDHAKEG9YACV9HCPJUEUKOYFNWDX"
        "CCJBIFQKYOXGRDHVTHEQUMHO999999999999999999999999999999999999999999999999999999999999"
        "999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
        "999",
        1, 1, "999999999999999999999999999999999999999999999999999999OVATEWFUX9ORCXAETEZCEJZVOXG",
        "HYZJPVGLNYMHKMC9TRQXNXSSHZZUOUBZRJMLZETENPQKTIECOSG9CFLNVWNMSPXQGCHMTZT9OCR9A9999",
        1507233573,
        "KTRETJZQNAZKOLFKJGQUYLSYVHTFJBE9MZCUOAWZXTFOHWMMZBPOFVGQCRSASCBKDQZRIXNILUZQ99999",
        "UXWJUGEJFXZGOKZUOLVIUWBKYXWAQBDUMZYLTJUBRFXUWAY9DZHVHXCOYAJKLFOBXYOPLIBHIHQV99999",
        "999999999999999999999999999999999999999999999999999999999999999999999999999999999", 0, "",
        "999999999999999999999999999", 0, 0, 0 });

  b.finalize();

  for (const auto& trx : b.getTransactions()) {
    EXPECT_EQ(trx.getBundle(),
              "OE9RXPMWDVHVQSDAQSUQBXAIBTFTEJWOFFD99CLBACFTVGLRNIMKSEMSAF9XZLGYMFAEAQXKUNCORMUAD");
  }
}

TEST(Bundle, AddTrytes) {
  IOTA::Models::Bundle b;

  //! add 3 transactions
  b.addTransaction({ ACCOUNT_1_ADDRESS_1_HASH, 1, "TAG", 2 });
  b.addTransaction({ ACCOUNT_1_ADDRESS_1_HASH, 1, "TAG", 2 });
  b.addTransaction({ ACCOUNT_1_ADDRESS_1_HASH, 1, "TAG", 2 });

  //! addTrytes testing different cases:
  //!  * padding
  //!  * not enough signatures provided
  //!  * reset of nonce, trunk and branch transaction
  b.addTrytes({ "ABC", "DEF" });

  EXPECT_EQ(b.getTransactions()[0].getSignatureFragments(), "ABC");
  EXPECT_EQ(b.getTransactions()[1].getSignatureFragments(), "DEF");
  EXPECT_EQ(
      b.getTransactions()[2].getSignatureFragments(),
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
      "99999999999999999999999999999999999999999999999999999999999999999999999");

  EXPECT_EQ(b.getTransactions()[0].getTrunkTransaction(),
            "999999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(b.getTransactions()[1].getTrunkTransaction(),
            "999999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(b.getTransactions()[2].getTrunkTransaction(),
            "999999999999999999999999999999999999999999999999999999999999999999999999999999999");

  EXPECT_EQ(b.getTransactions()[0].getBranchTransaction(),
            "999999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(b.getTransactions()[1].getBranchTransaction(),
            "999999999999999999999999999999999999999999999999999999999999999999999999999999999");
  EXPECT_EQ(b.getTransactions()[2].getBranchTransaction(),
            "999999999999999999999999999999999999999999999999999999999999999999999999999999999");

  EXPECT_EQ(b.getTransactions()[0].getNonce(), "999999999999999999999999999");
  EXPECT_EQ(b.getTransactions()[1].getNonce(), "999999999999999999999999999");
  EXPECT_EQ(b.getTransactions()[2].getNonce(), "999999999999999999999999999");
}
