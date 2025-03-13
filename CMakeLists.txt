cmake_minimum_required(VERSION 3.12)
project( opencv-benchmarks VERSION 0.0.0 LANGUAGES CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )
add_executable( cv-bench src/main.cpp src/classifier.cpp)
target_link_libraries( cv-bench ${OpenCV_LIBS} )


include(FetchContent)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
set(BENCHMARK_ENABLE_TESTING OFF)
FetchContent_Declare(
    google_benchmark
    GIT_REPOSITORY https://github.com/CodSpeedHQ/codspeed-cpp
    SOURCE_SUBDIR google_benchmark
    # GIT_TAG v1.0.0
    GIT_TAG origin/main
)
FetchContent_MakeAvailable(google_benchmark)
target_link_libraries(cv-bench benchmark::benchmark)

