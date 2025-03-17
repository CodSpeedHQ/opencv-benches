#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>

class ColorConversionFixture : public benchmark::Fixture {
 public:
  cv::Mat img;

  void SetUp(const ::benchmark::State&) override {
    img = cv::imread("assets/dog_bike_car.jpg");
    if (img.empty())
      throw std::runtime_error("Cannot open image");
  }
};

BENCHMARK_DEFINE_F(ColorConversionFixture, BM_ColorConversion)
(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    benchmark::DoNotOptimize(gray.data);
  }
}
BENCHMARK_REGISTER_F(ColorConversionFixture, BM_ColorConversion);
