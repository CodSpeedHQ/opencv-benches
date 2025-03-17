#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>

class ImageFixture : public benchmark::Fixture {
 public:
  cv::Mat img;

  void SetUp(const ::benchmark::State&) override {
    img = cv::imread("assets/dog_bike_car.jpg");
    if (img.empty())
      throw std::runtime_error("Cannot open image");
  }
};
