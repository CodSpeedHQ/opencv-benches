#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>
#include "fixtures.hpp"

BENCHMARK_DEFINE_F(ImageFixture, BM_ColorConversion)
(benchmark::State& state) {
  // Get the color conversion code from the argument
  int conversionCode = state.range(0);

  for (auto _ : state) {
    cv::Mat output;
    cv::cvtColor(img, output, conversionCode);
    benchmark::DoNotOptimize(output.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_ColorConversion_MultiStep)
(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat temp, output;
    cv::cvtColor(img, temp, cv::COLOR_BGR2HSV);
    cv::cvtColor(temp, output, cv::COLOR_HSV2RGB);
    benchmark::DoNotOptimize(output.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_ChannelOperations)
(benchmark::State& state) {
  for (auto _ : state) {
    std::vector<cv::Mat> channels;
    cv::split(img, channels);
    cv::Mat merged;
    cv::merge(channels, merged);
    benchmark::DoNotOptimize(merged.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_ColorConversion_BitDepth)
(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat float_img, output;
    img.convertTo(float_img, CV_32F, 1.0 / 255.0);
    cv::cvtColor(float_img, output, cv::COLOR_BGR2HSV);
    benchmark::DoNotOptimize(output.data);
  }
}

BENCHMARK_REGISTER_F(ImageFixture, BM_ColorConversion)
    ->Arg(cv::COLOR_BGR2GRAY)  // Test BGR to Grayscale
    ->Arg(cv::COLOR_BGR2HSV)   // Test BGR to HSV
    ->Arg(cv::COLOR_BGR2Lab)   // Test BGR to Lab
    ->Arg(cv::COLOR_BGR2RGB);  // Test BGR to RGB
BENCHMARK_REGISTER_F(ImageFixture, BM_ColorConversion_MultiStep);
BENCHMARK_REGISTER_F(ImageFixture, BM_ChannelOperations);
BENCHMARK_REGISTER_F(ImageFixture, BM_ColorConversion_BitDepth);

BENCHMARK_MAIN();
