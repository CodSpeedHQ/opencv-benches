#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>

static void BM_ReadImage(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat img = cv::imread("assets/dog_bike_car.jpg");
    benchmark::DoNotOptimize(img.data);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_ReadImage);
