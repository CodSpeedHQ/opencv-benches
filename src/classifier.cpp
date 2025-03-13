// https://docs.opencv.org/4.x/db/d28/tutorial_cascade_classifier.html
//
#include <benchmark/benchmark.h>
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"

int detect(const std::string& cascadePath,
           const std::string& imagePath,
           bool showImage = false) {
  cv::CascadeClassifier cat_cascade;
  if (!cat_cascade.load(cascadePath)) {
    std::cerr << "Error loading cat cascade classifier file" << std::endl;
    return -1;
  }

  cv::Mat image = cv::imread(imagePath);
  if (image.empty()) {
    std::cerr << "Error loading image" << std::endl;
    return -1;
  }

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

static void BM_ClassifyCat(benchmark::State& state) {
  for (auto _ : state) {
    int result = detect("assets/haarcascade_frontalcatface.xml",
                        "assets/cat_on_table.jpg");
    if (result != 0) {
      state.SkipWithError("Error in detect()");
    }
  }
}

BENCHMARK(BM_ClassifyCat);

#ifdef TESTING
#include <iostream>
int main() {
  int result = detect("assets/haarcascade_frontalcatface.xml",
                      "assets/cat_on_table.jpg");
  std::cout << "Result: " << result << std::endl;
}
#endif
