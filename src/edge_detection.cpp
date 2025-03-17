#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>

class EdgeDetectionFixture : public benchmark::Fixture {
 public:
  cv::Mat img;

  void SetUp(const ::benchmark::State&) override {
    img = cv::imread("assets/dog_bike_car.jpg");
    if (img.empty())
      throw std::runtime_error("Cannot open image");
  }
};

BENCHMARK_DEFINE_F(EdgeDetectionFixture, BM_Canny)(benchmark::State& state) {
  double low = state.range(0);
  double high = state.range(1);
  for (auto _ : state) {
    cv::Mat edges;
    cv::Canny(img, edges, low, high);
    benchmark::DoNotOptimize(edges.data);
  }
}

BENCHMARK_REGISTER_F(EdgeDetectionFixture, BM_Canny)
    ->Args({50, 150})
    ->Args({75, 175})
    ->Args({100, 200});
