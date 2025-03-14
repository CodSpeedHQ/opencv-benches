#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>

// Shared image for all filters in this file
static cv::Mat GetImage() {
  static cv::Mat img = cv::imread("assets/dog_bike_car.jpg");
  if (img.empty())
    throw std::runtime_error("Cannot open image");
  return img;
}

static void BM_GaussianBlur(benchmark::State& state) {
  cv::Mat img = GetImage();
  int kernel_size = state.range(0);

  for (auto _ : state) {
    cv::Mat blurred;
    cv::GaussianBlur(img, blurred, {kernel_size, kernel_size}, 0);
    benchmark::DoNotOptimize(blurred.data);
  }
}

static void BM_MedianBlur(benchmark::State& state) {
  cv::Mat img = GetImage();
  int kernel_size = state.range(0);

  for (auto _ : state) {
    cv::Mat blurred;
    cv::medianBlur(img, blurred, kernel_size);
    benchmark::DoNotOptimize(blurred.data);
  }
}

static void BM_Sobel(benchmark::State& state) {
  cv::Mat img = GetImage();
  int kernel_size = state.range(0);

  for (auto _ : state) {
    cv::Mat grad;
    cv::Sobel(img, grad, CV_16S, 1, 0, kernel_size);
    benchmark::DoNotOptimize(grad.data);
  }
}

// Register kernel sizes for all filters
BENCHMARK(BM_GaussianBlur)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(9)
    ->Arg(11)
    ->Arg(13)
    ->Arg(15);
BENCHMARK(BM_MedianBlur)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(9)
    ->Arg(11)
    ->Arg(13)
    ->Arg(15);
BENCHMARK(BM_Sobel)->Arg(3)->Arg(5)->Arg(7)->Arg(9)->Arg(11)->Arg(13)->Arg(15);
