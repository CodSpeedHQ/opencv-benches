#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>
#include "fixtures.hpp"

BENCHMARK_DEFINE_F(ImageFixture, BM_Rotate)(benchmark::State& state) {
  double angle = state.range(0);
  cv::Point2f center(img.cols / 2.0f, img.rows / 2.0f);
  cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);

  for (auto _ : state) {
    cv::Mat rotated;
    cv::warpAffine(img, rotated, rot_mat, img.size());
    benchmark::DoNotOptimize(rotated.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_Scale)(benchmark::State& state) {
  double scale = state.range(0) / 100.0;
  for (auto _ : state) {
    cv::Mat resized;
    cv::resize(img, resized, cv::Size(), scale, scale);
    benchmark::DoNotOptimize(resized.data);
  }
}

BENCHMARK_DEFINE_F(ImageFixture, BM_Crop)(benchmark::State& state) {
  int crop_size = state.range(0);
  cv::Rect roi((img.cols - crop_size) / 2, (img.rows - crop_size) / 2,
               crop_size, crop_size);
  for (auto _ : state) {
    cv::Mat cropped = img(roi).clone();
    benchmark::DoNotOptimize(cropped.data);
  }
}

BENCHMARK_REGISTER_F(ImageFixture, BM_Rotate)->Arg(30)->Arg(45)->Arg(90);
BENCHMARK_REGISTER_F(ImageFixture, BM_Scale)->Arg(50)->Arg(200);
BENCHMARK_REGISTER_F(ImageFixture, BM_Crop)->Arg(100)->Arg(200)->Arg(500);
BENCHMARK_MAIN();
