# Go to keccak directory
cd $CMAKE_SOURCE_DIR/external/keccak

# build source package 
make $KECCAK_ARCH_OPTIMIZATION/libkeccak.a.pack
tar xfv bin/"$KECCAK_ARCH_OPTIMIZATION"_libkeccak.a.tar.gz

# build library
# notice we only use gcc as the library does not seem compatible with clang as of now
gcc -fomit-frame-pointer -O2 -g0 -march=native -mtune=native -I $KECCAK_ARCH_OPTIMIZATION $FORWARD_FLAGS $KECCAK_ARCH_OPTIMIZATION/libkeccak.a/*.c -c
ar rcs libkeccak.a *.o
