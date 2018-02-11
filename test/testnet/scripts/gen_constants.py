#!/usr/bin/python
from iota import Iota
from iota import Address, ProposedTransaction, ProposedBundle, Tag, Transaction
from iota import TryteString
from iota.crypto.signing import KeyGenerator


#
# Helper to fetch and generate account info
#
def gen_account_info(account_idx, seed, nb_addrs):
    # api connection
    api           = Iota('http://localhost:14265', seed)

    # account info
    account_data  = api.get_account_data(stop=nb_addrs)
    fund          = account_data['balance']
    addrs         = account_data['addresses']
    addrs_fund    = api.getBalances(addresses=addrs)['balances']

    # generate
    account_info = \
"""
//!
//! Account %d
//!
static const std::string ACCOUNT_%d_SEED = "%s";
static const int64_t     ACCOUNT_%d_FUND = %d;
""" % (account_idx, account_idx, seed, account_idx, fund)

    for i in range(0, len(addrs)):
        addr_idx = i + 1
        account_info += \
"""
static const std::string ACCOUNT_%d_ADDRESS_%d_HASH                  = "%s";
static const std::string ACCOUNT_%d_ADDRESS_%d_HASH_WITHOUT_CHECKSUM = "%s";
static const int64_t ACCOUNT_%d_ADDRESS_%d_FUND                      = %d;
""" % (account_idx, addr_idx, addrs[i].with_valid_checksum(), account_idx, addr_idx, addrs[i], account_idx, addr_idx, addrs_fund[i])

    return account_info + '\n'


#
# Helper function to fetch and generate bundle information
#
def gen_bundle_info_for_transfer(bundle_idx, label, seed, dst_addr, value):
    # api
    api = Iota('http://localhost:14265', seed)

    # find all transactions for address
    trxs   = api.find_transactions(addresses=[dst_addr])['hashes']
    bundle = None

    # try to find the right bundle
    for trx in trxs:
        try:
            trx_bundles = api.get_bundles(trx)['bundles']

            for trx_bundle in trx_bundles:
                try:
                    if trx_bundle.transactions[0].value == value and trx_bundle.transactions[0].address == dst_addr:
                        bundle = trx_bundle
                        break
                except:
                    pass

            if bundle:
                break
        except:
            pass

    # If trx could not be found, raise and stop now
    if not bundle:
        raise BaseException("Could not find bundle for trx %s (%di)" % (dst_addr, value))

    bundle_info = \
"""
//!
//! Bundle %d
//! %s
//!
static const std::string BUNDLE_%d_HASH = "%s";
""" % (bundle_idx, label, bundle_idx, bundle.hash)

    for i in range(0, len(bundle.transactions)):
        trx_idx = i + 1
        trx     = bundle.transactions[i]
        bundle_info += \
"""
static const std::string BUNDLE_%d_TRX_%d_HASH                      = "%s";
static const std::string BUNDLE_%s_TRX_%s_ADDRESS                   = "%s";
static const std::string BUNDLE_%d_TRX_%d_ADDRESS_WITHOUT_CHECKSUM  = "%s";
static const std::string BUNDLE_%d_TRX_%d_TRYTES                    = "%s";
static const std::string BUNDLE_%d_TRX_%d_SIGNATURE_FRAGMENT        = "%s";
static const int64_t     BUNDLE_%d_TRX_%d_CURRENT_INDEX             = %d;
static const int64_t     BUNDLE_%d_TRX_%d_LAST_INDEX                = %d;
static const std::string BUNDLE_%d_TRX_%d_NONCE                     = "%s";
static const std::string BUNDLE_%d_TRX_%d_TAG                       = "%s";
static const int64_t     BUNDLE_%d_TRX_%d_TS                        = %d;
static const std::string BUNDLE_%d_TRX_%d_TRUNK                     = "%s";
static const std::string BUNDLE_%d_TRX_%d_BRANCH                    = "%s";
static const int64_t     BUNDLE_%d_TRX_%d_VALUE                     = %d;
""" % (
    bundle_idx, trx_idx, trx.hash,
    bundle_idx, trx_idx, trx.address.with_valid_checksum(),
    bundle_idx, trx_idx, trx.address,
    bundle_idx, trx_idx, trx.as_tryte_string(),
    bundle_idx, trx_idx, trx.signature_message_fragment,
    bundle_idx, trx_idx, trx.current_index,
    bundle_idx, trx_idx, trx.last_index,
    bundle_idx, trx_idx, trx.nonce,
    bundle_idx, trx_idx, trx.tag,
    bundle_idx, trx_idx, trx.timestamp,
    bundle_idx, trx_idx, trx.trunk_transaction_hash,
    bundle_idx, trx_idx, trx.branch_transaction_hash,
    bundle_idx, trx_idx, trx.value
)

    return bundle_info


#
# Helper function to generate list of all transactions for all bundles for a given account
#
def gen_account_bundles_list(account_idx, seed):
    # api
    api = Iota('http://localhost:14265', seed)

    # account info
    account_data  = api.get_account_data()
    bundles       = account_data['bundles']

    account_bundles_list = \
"""
//!
//! Account 1 Detailed transactions
//!
"""

    for i in range(0, len(bundles)):
        bundle_idx = i + 1
        bundle     = bundles[i]

        for j in range(0, len(bundle.transactions)):
            trx_idx = j + 1
            trx     = bundle.transactions[j]

            account_bundles_list += \
"""
static const std::string ACCOUNT_%s_BUNDLE_%s_TRX_%s_TRYTES = "%s";
""" % (account_idx, bundle_idx, trx_idx, trx.as_tryte_string())

    return account_bundles_list


#
# Header
#
constants_hpp_content = \
"""//
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

#pragma once

#include <string>
"""

# precompute data
account_3_addr_1 = "E9LVPMKJIAGCIPVKMUOYTQMSYAUQDUMEYUUCLXRQUWJJ9JXRDXQNGIOUPQVIMIWHFIRXD9QSYOP9KG9BW"
account_1_seed   = "SXDHBTSTV9YHWKFFAZBHQXJTQHTO9HJMDBZHOJDKV9MMAODELRICQAQMEOCZXZKO9USMBUAKJCAYTF9TM"
account_2_seed   = "S9YOBZWUIHQFGHQCUOFCKHFR99IJMSZNNHUDXRAGDZKLGEBGPNDWROALSUODRJNMFFQHDVNISRMVMPVNE"
account_3_seed   = "UYMUEUOCKNROIJPNFFDLBP9GCQUJFRLIBQ9SMICMHSHSOXUZLOWHFJDPEEPUESUXJEAJFTICCEGPMMHKO"
account_4_seed   = "NG9VUE9RBOLTPNAHFVWBPF9QELYLBNX9ZNIKYJZKWASZWJCMXZ9QIXNMAYDO9DJAZ9EBUBKDEFCUVQFXG"
account_5_seed   = "UYXMZDTITKOAPKPFCAZYB9DTPJ9VARFKCWVSYIOZROLBSUJECBLBZA99TTBFJTPUXEYN9PETLVENOHRKJ"


# Account info
constants_hpp_content += gen_account_info(1, account_1_seed, 7)
constants_hpp_content += gen_account_info(2, account_2_seed, 6)
constants_hpp_content += gen_account_info(3, account_3_seed, 9)
constants_hpp_content += gen_account_info(4, account_4_seed, 1)
constants_hpp_content += gen_account_info(5, account_5_seed, 5)

# Bundle info
constants_hpp_content += gen_bundle_info_for_transfer(1, "Trx from account 2 to account 3", account_2_seed, account_3_addr_1, 42)
constants_hpp_content += gen_bundle_info_for_transfer(2, "Initial funding of account_3:address_1", account_2_seed, account_3_addr_1, 0)

# account bundles
constants_hpp_content += gen_account_bundles_list(2, account_2_seed)

# Misc
constants_hpp_content += \
"""
//!
//! Misc
//!

static const std::string EMPTY_SIGNATURE_FRAGMENT =
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999999"
    "9999999999999999999999999";

static const int POW_LEVEL = 9;
"""

print constants_hpp_content
