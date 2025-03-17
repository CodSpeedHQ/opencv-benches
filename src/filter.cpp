#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>

class FilterFixture : public benchmark::Fixture {
 public:
  cv::Mat img;

  void SetUp(const ::benchmark::State&) override {
    img = cv::imread("assets/dog_bike_car.jpg");
    if (img.empty())
      throw std::runtime_error("Cannot open image");
  }
};

BENCHMARK_DEFINE_F(FilterFixture, BM_GaussianBlur)(benchmark::State& state) {
  int kernel_size = state.range(0);
  for (auto _ : state) {
    cv::Mat blurred;
    cv::GaussianBlur(img, blurred, cv::Size(kernel_size, kernel_size), 0);
    benchmark::DoNotOptimize(blurred.data);
  }
}

BENCHMARK_DEFINE_F(FilterFixture, BM_MedianBlur)(benchmark::State& state) {
  int kernel_size = state.range(0);
  for (auto _ : state) {
    cv::Mat blurred;
    cv::medianBlur(img, blurred, kernel_size);
    benchmark::DoNotOptimize(blurred.data);
  }
}

BENCHMARK_DEFINE_F(FilterFixture, BM_Sobel)(benchmark::State& state) {
  int kernel_size = state.range(0);
  for (auto _ : state) {
    cv::Mat grad;
    cv::Sobel(img, grad, CV_16S, 1, 0, kernel_size);
    benchmark::DoNotOptimize(grad.data);
  }
}

BENCHMARK_REGISTER_F(FilterFixture, BM_GaussianBlur)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(9)
    ->Arg(11)
    ->Arg(13)
    ->Arg(15);
BENCHMARK_REGISTER_F(FilterFixture, BM_MedianBlur)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(9)
    ->Arg(11)
    ->Arg(13)
    ->Arg(15);
BENCHMARK_REGISTER_F(FilterFixture, BM_Sobel)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(9)
    ->Arg(11)
    ->Arg(13)
    ->Arg(15);
