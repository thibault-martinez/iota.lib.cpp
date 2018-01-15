#!/usr/bin/python
from iota import Iota
from iota import Address, ProposedTransaction, ProposedBundle, Tag, Transaction
from iota import TryteString
from iota.crypto.signing import KeyGenerator

#
# Create a new bundle transaction
# Send from 42 iota account 2 to account 3
#

# Connect to the node
api = Iota('http://localhost:14265', "S9YOBZWUIHQFGHQCUOFCKHFR99IJMSZNNHUDXRAGDZKLGEBGPNDWROALSUODRJNMFFQHDVNISRMVMPVNE")

# Trx setup
output_trx = ProposedTransaction(
    address = Address("E9LVPMKJIAGCIPVKMUOYTQMSYAUQDUMEYUUCLXRQUWJJ9JXRDXQNGIOUPQVIMIWHFIRXD9QSYOP9KG9BWARSINOJ9W"),
    message = TryteString.from_string("Sending some money"),
    tag     = Tag("PACIFICSOUND"),
    value   = 42)

# Propagate
api.send_transfer(1, [output_trx])
