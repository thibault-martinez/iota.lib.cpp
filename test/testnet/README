# IOTA Private TestNet
## Introduction
Running tests on the public IOTA network is not recommended for multiple reasons:
* Possible network congestions
* Nodes are subject to changes (not available anymore, different API, ...)
* Funds on an address are subject to changes

IOTA provide an alternative network, a public network of test `IOTA TestNet`.
However, though it is a great tool for manual testing, it is not really the best tool for running automated tests:
* Still possible network congestions
* Still having nodes subject to changes
* Still funds on an address are subject to changes
* The network is regularly reset which mean it is hard to maintain a stable environment

Thus, we decided to use a `private IOTA TestNet`. We basically create our own initial snapshot and run our own IRI, not connected to any other nodes.
This allows us to:
* Create a stable environment
* Run our own node without the need to setup some neighbors (which is great when running a node inside several different Travis build with unknown host/port)
* Have great flexibility on the state of the network thanks to a configurable snapshot

## How to
### 1. Generate a snapshot
Special thanks to [schierlm/private-iota-testnet](https://github.com/schierlm/private-iota-testnet).

A snapshot is a state of a network at a given time. In our case, this is the initial configuration.
It sets the repartition of the IOTA supply to specific addresses corresponding to specific seeds.

1. Download [schierlm/private-iota-testnet](https://github.com/schierlm/private-iota-testnet)
2. Build `mvn package`
3. Run `java -jar target/iota-testnet-tools-0.1-SNAPSHOT-jar-with-dependencies.jar SnapshotBuilder` and specify the token repartition
4. You now got your own custom snapshot inside `Snapshot.txt`

### 2. Run IRI
1. Download [iotaledger/iri](https://github.com/iotaledger/iri)
2. Replace `src/main/java/com/iota/iri/Snapshot.java` with our `test/testnet/Snapshot.java` (this is a modified version that do not verify the Snapshot signature)
3. Copy the `Snapshot.txt` file generated previously into `src/main/resources`
4. Build `mvn clean compile && mvn package`
5. Run `java -jar target/iri-1.4.1.6.jar --testnet -p 14265`

### 3. Run a coordinator to generate a milestone
Special thanks to [schierlm/private-iota-testnet](https://github.com/schierlm/private-iota-testnet).

Before being able to run any command on the IOTA node, you need to set a first milestone by running the coordinator.

1. Download [schierlm/private-iota-testnet](https://github.com/schierlm/private-iota-testnet)
2. Build `mvn package`
3. Run `java -jar target/iota-testnet-tools-0.1-SNAPSHOT-jar-with-dependencies.jar Coordinator localhost 14265`

### 4. Attach the addresses
In order to use the addresses of each seed set in the snapshot and to access the funds, you need to attach each address to the tangle first.

1. Update the `test/testnet/attach_snapshot_to_tangle.py` script with the seeds, addresses and funds of your snapshot
2. Make sure IRI is running and that you run the coordinator at least once
3. Install [iotaledger/iota.lib.py](https://github.com/iotaledger/iota.lib.py)
4. Run the `test/testnet/attach_snapshot_to_tangle.py` script
5. If any failure is reported, you may need to start over and investigate the reason of the failure
