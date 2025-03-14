clean:
    rm -rf build

run:
    ./build/cv-bench

build:
    mkdir -p build
    cd build && cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo ..
    cd build && ninja -j16

build-instrumentation:
    mkdir -p build
    cd build && cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCODSPEED_MODE=instrumentation ..
    cd build && ninja -j16

build-walltime:
    mkdir -p build
    cd build && cmake -GNinja -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCODSPEED_MODE=walltime ..
    cd build && ninja -j16

@fmt:
    clang-format -i src/*.cpp
