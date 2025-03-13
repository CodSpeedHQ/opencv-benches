clean:
    rm -rf build

run: build
    ./build/cv-bench

build:
    mkdir -p build
    cd build && cmake -GNinja -DCMAKE_BUILD_TYPE=Release ..
    cd build && ninja -j16

@fmt: 
    clang-format -i src/*.cpp 
