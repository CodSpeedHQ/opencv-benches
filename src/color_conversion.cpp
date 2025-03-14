#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>

static void BM_ColorConversion(benchmark::State& state) {
  static cv::Mat img = cv::imread("assets/dog_bike_car.jpg");
  if (img.empty())
    throw std::runtime_error("Cannot open image");

  for (auto _ : state) {
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    benchmark::DoNotOptimize(gray.data);
  }
}
BENCHMARK(BM_ColorConversion);
