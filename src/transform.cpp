#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>

static cv::Mat GetImage() {
  static cv::Mat img = cv::imread("assets/dog_bike_car.jpg");
  if (img.empty())
    throw std::runtime_error("Cannot open image");
  return img;
}

static void BM_Rotate(benchmark::State& state) {
  cv::Mat img = GetImage();
  double angle = state.range(0);
  cv::Point2f center(img.cols / 2.0f, img.rows / 2.0f);
  cv::Mat rot_mat = cv::getRotationMatrix2D(center, angle, 1.0);

  for (auto _ : state) {
    cv::Mat rotated;
    cv::warpAffine(img, rotated, rot_mat, img.size());
    benchmark::DoNotOptimize(rotated.data);
  }
}

static void BM_Scale(benchmark::State& state) {
  cv::Mat img = GetImage();
  double scale = state.range(0) / 100.0;

  for (auto _ : state) {
    cv::Mat resized;
    cv::resize(img, resized, {}, scale, scale);
    benchmark::DoNotOptimize(resized.data);
  }
}

BENCHMARK(BM_Rotate)->Arg(30)->Arg(45)->Arg(90);
BENCHMARK(BM_Scale)->Arg(50)->Arg(200);
