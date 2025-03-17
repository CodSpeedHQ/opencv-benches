// https://docs.opencv.org/4.x/db/d28/tutorial_cascade_classifier.html
//
#include <benchmark/benchmark.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"

int detect(cv::CascadeClassifier& cat_cascade,
           const cv::Mat& image,
           bool showImage = false) {
  // Convert the image to grayscale
  cv::Mat gray;
  cv::cvtColor(image, gray, cv::COLOR_BGR2GRAY);

  // Equalize histogram to enhance contrast
  cv::equalizeHist(gray, gray);

  // Vector to hold the detected cats
  std::vector<cv::Rect> cats;

  // Detect cats in the image
  cat_cascade.detectMultiScale(gray, cats, 1.1, 3, 0 | cv::CASCADE_SCALE_IMAGE,
                               cv::Size(30, 30));

  if (showImage) {
    // Draw rectangles around the detected cats
    for (size_t i = 0; i < cats.size(); i++) {
      cv::rectangle(image, cats[i], cv::Scalar(255, 0, 0), 2);
    }

    // Display the image with detected cats
    cv::imshow("Cat Detection", image);
    cv::waitKey(0);
  }
  return 0;
}

class ClassifierFixture : public benchmark::Fixture {
 public:
  cv::Mat img;
  cv::CascadeClassifier cat_cascade;

  void SetUp(const ::benchmark::State&) override {
    img = cv::imread("assets/dog_bike_car.jpg");
    if (img.empty())
      throw std::runtime_error("Cannot open image");

    cat_cascade.load("assets/haarcascade_frontalcatface.xml");
    if (cat_cascade.empty())
      throw std::runtime_error("Cannot load cascade");
  }
};

BENCHMARK_DEFINE_F(ClassifierFixture, BM_ClassifyCat)(benchmark::State& state) {
  for (auto _ : state) {
    int result = detect(cat_cascade, img);
    if (result != 0) {
      state.SkipWithError("Error in detect()");
    }
  }
}
BENCHMARK_REGISTER_F(ClassifierFixture, BM_ClassifyCat);
