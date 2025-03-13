clean:
    rm -rf build

run: build
    ./build/benchmark

build:
    mkdir -p build
    cd build && cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
    cd build && ninja -j16
