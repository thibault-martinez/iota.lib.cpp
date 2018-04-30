# Go to keccak directory
cd $CMAKE_SOURCE_DIR/external/keccak

# Build deps directory
mkdir -p $CMAKE_SOURCE_DIR/deps/include/keccak

# Move includes and library
cp $KECCAK_ARCH_OPTIMIZATION/libkeccak.a/*.h $CMAKE_SOURCE_DIR/deps/include/keccak
cp libkeccak.a $CMAKE_SOURCE_DIR/deps/lib
