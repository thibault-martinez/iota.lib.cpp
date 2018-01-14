#!/usr/bin/python
from iota import Iota
from iota import Address, ProposedTransaction, ProposedBundle, Tag, Transaction
from iota import TryteString
from iota.crypto.signing import KeyGenerator

#
# Create a new bundle transaction
# Use same address for input and output address to key the state of network unchanged, just adding a trx
#
#   From seed: SXDHBTSTV9YHWKFFAZBHQXJTQHTO9HJMDBZHOJDKV9MMAODELRICQAQMEOCZXZKO9USMBUAKJCAYTF9TM
#   From addr: FWPSSVXWSJRZLKWYKSVJIURDU9IKBAVPBJVTAXDJTYCJHSRUTKLVWKIN9AEEFNMONNDKVAIAXVRKLQSLCHZRXZWU9C
#   To seed:   SXDHBTSTV9YHWKFFAZBHQXJTQHTO9HJMDBZHOJDKV9MMAODELRICQAQMEOCZXZKO9USMBUAKJCAYTF9TM
#   To addr:   FWPSSVXWSJRZLKWYKSVJIURDU9IKBAVPBJVTAXDJTYCJHSRUTKLVWKIN9AEEFNMONNDKVAIAXVRKLQSLCHZRXZWU9C
#   Amount:    832480
#
#

# Connect to the node
api = Iota('http://localhost:14265', "SXDHBTSTV9YHWKFFAZBHQXJTQHTO9HJMDBZHOJDKV9MMAODELRICQAQMEOCZXZKO9USMBUAKJCAYTF9TM")

# Send transaction to myself containing all fund of the input address
output_trx = ProposedTransaction(
    address = Address("FWPSSVXWSJRZLKWYKSVJIURDU9IKBAVPBJVTAXDJTYCJHSRUTKLVWKIN9AEEFNMONNDKVAIAXVRKLQSLCHZRXZWU9C"),
    message = TryteString.from_string("Sending some money to MySeLf"),
    tag     = Tag("PACIFICSOUND"),
    value   = 832480)

# The input address with the exact amount to send
input_addr = Address(
    'FWPSSVXWSJRZLKWYKSVJIURDU9IKBAVPBJVTAXDJTYCJHSRUTKLVWKIN9AEEFNMONNDKVAIAXVRKLQSLCHZRXZWU9C',
    balance        = 832480,
    key_index      = 0,
    security_level = 1
)

# Propagate
api.send_transfer(1, [output_trx], [input_addr])
