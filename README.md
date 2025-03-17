# opencv-benches

A benchmarking suite for comparing performance of various opencv library components using Google Benchmark.

## Requirements

- CMake 3.14+
- C++14 compiler
- OpenCV 4.x
- [Just](https://github.com/casey/just) command runner
- Ninja

## Build

Using the just command runner:
```bash
just clean    # Make sure that there's no 'build/' dir
just build
just run
```

Or by doing it manually:
```bash
mkdir build && cd build

# Without codspeed
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo ..

# With Codspeed instrumentation
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCODSPEED_MODE=instrumentation ..

# With regular timing based benchmarks
cmake -DCMAKE_BUILD_TYPE=RelWithDebInfo -DCODSPEED_MODE=walltime ..

make
```

## Run

```bash
cp -r assets/ build/

# Run individual component benchmarks
./build/classifier
./build/color
./build/filter
./build/image
./build/transform

# Run all benchmarks with a single command
cmake --build ./build --target run_all_benchmarks

# Pass arguments to all benchmarks
cmake --build . --target run_all_benchmarks -- --benchmark_filter=BM_Boost

# Run with regex filter
./build/transform --benchmark_filter="BM_Rotate"

# List available benchmarks
./build/transform --benchmark_list_tests
```


## Benchmark Categories

- **Classifier**: Detects objects in images.
- **Color**: Converts colors between different color spaces.
- **Image**: Everything related to image processing
- **Filter**: Applies various image filters (e.g. blur, sharpen, edge detection).
- **Transform**: Performs image transformations (e.g. rotation, scaling, cropping, ...)

## References

- https://docs.opencv.org/4.x/db/df5/tutorial_linux_gcc_cmake.html
- https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html
- https://docs.opencv.org/4.x/index.html
