cmake_minimum_required(VERSION 3.12)
project( opencv-benchmarks VERSION 0.0.0 LANGUAGES CXX)
find_package( OpenCV REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )

# Configure Google Benchmark
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

# Configure the executables
#
set(BENCHMARKS classifier color filter image transform)
foreach(benchmark IN LISTS BENCHMARKS)
  add_executable(${benchmark} src/${benchmark}.cpp)
  target_link_libraries(${benchmark}
    benchmark::benchmark
    ${OpenCV_LIBS}
  )
endforeach()


add_custom_target(run_all_benchmarks
  COMMAND ${CMAKE_COMMAND} -E echo "Running all benchmarks..."
)

# Make each benchmark depend on the run_all_benchmarks target
foreach(benchmark IN LISTS BENCHMARKS)
  add_custom_command(
    TARGET run_all_benchmarks
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Running ${benchmark}..."
    COMMAND $<TARGET_FILE:${benchmark}>
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
  )
endforeach()
