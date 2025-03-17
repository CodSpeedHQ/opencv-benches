#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>
#include "fixtures.hpp"

BENCHMARK_DEFINE_F(ImageFixture, BM_GaussianBlur)(benchmark::State& state) {
  int kernel_size = state.range(0);
  for (auto _ : state) {
    cv::Mat blurred;
    cv::GaussianBlur(img, blurred, cv::Size(kernel_size, kernel_size), 0);
    benchmark::DoNotOptimize(blurred.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_MedianBlur)(benchmark::State& state) {
  int kernel_size = state.range(0);
  for (auto _ : state) {
    cv::Mat blurred;
    cv::medianBlur(img, blurred, kernel_size);
    benchmark::DoNotOptimize(blurred.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_Sobel)(benchmark::State& state) {
  int kernel_size = state.range(0);
  for (auto _ : state) {
    cv::Mat grad;
    cv::Sobel(img, grad, CV_16S, 1, 0, kernel_size);
    benchmark::DoNotOptimize(grad.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_Canny)(benchmark::State& state) {
  double low = state.range(0);
  double high = state.range(1);
  for (auto _ : state) {
    cv::Mat edges;
    cv::Canny(img, edges, low, high);
    benchmark::DoNotOptimize(edges.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_Laplacian)(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat dst;
    cv::Laplacian(img, dst, CV_16S);
    cv::convertScaleAbs(dst, dst);
    benchmark::DoNotOptimize(dst.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_Scharr)(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat grad_x, grad_y;
    cv::Mat abs_grad_x, abs_grad_y;
    cv::Mat grad;

    cv::Scharr(img, grad_x, CV_16S, 1, 0);
    cv::Scharr(img, grad_y, CV_16S, 0, 1);

    cv::convertScaleAbs(grad_x, abs_grad_x);
    cv::convertScaleAbs(grad_y, abs_grad_y);
    cv::addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);

    benchmark::DoNotOptimize(grad.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_Sharpen)(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat kernel =
        (cv::Mat_<float>(3, 3) << -1, -1, -1, -1, 9, -1, -1, -1, -1);
    cv::Mat sharpened;
    cv::filter2D(img, sharpened, -1, kernel);
    benchmark::DoNotOptimize(sharpened.data);
  }
}

BENCHMARK_REGISTER_F(ImageFixture, BM_GaussianBlur)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(9)
    ->Arg(11)
    ->Arg(13)
    ->Arg(15);
BENCHMARK_REGISTER_F(ImageFixture, BM_MedianBlur)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(9)
    ->Arg(11)
    ->Arg(13)
    ->Arg(15);
BENCHMARK_REGISTER_F(ImageFixture, BM_Sobel)
    ->Arg(3)
    ->Arg(5)
    ->Arg(7)
    ->Arg(9)
    ->Arg(11)
    ->Arg(13)
    ->Arg(15);
BENCHMARK_REGISTER_F(ImageFixture, BM_Canny)
    ->Args({50, 150})
    ->Args({75, 175})
    ->Args({100, 200});
BENCHMARK_REGISTER_F(ImageFixture, BM_Laplacian);
BENCHMARK_REGISTER_F(ImageFixture, BM_Scharr);
BENCHMARK_REGISTER_F(ImageFixture, BM_Sharpen);
BENCHMARK_MAIN();
