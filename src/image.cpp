#include <benchmark/benchmark.h>
#include <opencv2/opencv.hpp>
#include "fixtures.hpp"

static void BM_ReadImage(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat img = cv::imread("assets/dog_bike_car.jpg");
    benchmark::DoNotOptimize(img.data);
    benchmark::ClobberMemory();
  }
}
BENCHMARK(BM_ReadImage);

BENCHMARK_F(ImageFixture, Resize)(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat resized;
    cv::resize(img, resized, cv::Size(640, 480));
    benchmark::DoNotOptimize(resized.data);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, GaussianBlur)(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat blurred;
    cv::GaussianBlur(img, blurred, cv::Size(5, 5), 1.5);
    benchmark::DoNotOptimize(blurred.data);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, Grayscale)(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
    benchmark::DoNotOptimize(gray.data);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, Threshold)(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat thresh;
    cv::threshold(img, thresh, 127, 255, cv::THRESH_BINARY);
    benchmark::DoNotOptimize(thresh.data);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, AdaptiveThreshold)(benchmark::State& state) {
  cv::Mat gray;
  cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
  for (auto _ : state) {
    cv::Mat thresh;
    cv::adaptiveThreshold(gray, thresh, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C,
                          cv::THRESH_BINARY, 11, 2);
    benchmark::DoNotOptimize(thresh.data);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, Sobel)(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat sobel;
    cv::Sobel(img, sobel, CV_64F, 1, 0, 3);
    benchmark::DoNotOptimize(sobel.data);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, Laplacian)(benchmark::State& state) {
  for (auto _ : state) {
    cv::Mat laplacian;
    cv::Laplacian(img, laplacian, CV_64F);
    benchmark::DoNotOptimize(laplacian.data);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, FindContours)(benchmark::State& state) {
  cv::Mat gray, thresh;
  cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);
  cv::threshold(gray, thresh, 127, 255, cv::THRESH_BINARY);
  for (auto _ : state) {
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresh, contours, hierarchy, cv::RETR_TREE,
                     cv::CHAIN_APPROX_SIMPLE);
    benchmark::DoNotOptimize(contours.data());
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, CalcHist)(benchmark::State& state) {
  cv::Mat hsv;
  cv::cvtColor(img, hsv, cv::COLOR_BGR2HSV);
  for (auto _ : state) {
    cv::Mat hist;
    float range[] = {0, 180};
    const float* histRange = {range};
    int histSize[] = {180};
    int channels[] = {0};
    cv::calcHist(&hsv, 1, channels, cv::Mat(), hist, 1, histSize, &histRange);
    benchmark::DoNotOptimize(hist.data);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, SIFT)(benchmark::State& state) {
  cv::Ptr<cv::SIFT> sift = cv::SIFT::create();
  for (auto _ : state) {
    std::vector<cv::KeyPoint> keypoints;
    cv::Mat descriptors;
    sift->detectAndCompute(img, cv::noArray(), keypoints, descriptors);
    benchmark::DoNotOptimize(keypoints.data());
    benchmark::ClobberMemory();
  }
}

BENCHMARK_F(ImageFixture, Warpaffine)(benchmark::State& state) {
  cv::Point2f srcTri[3];
  cv::Point2f dstTri[3];
  srcTri[0] = cv::Point2f(0.f, 0.f);
  srcTri[1] = cv::Point2f(img.cols - 1.f, 0.f);
  srcTri[2] = cv::Point2f(0.f, img.rows - 1.f);
  dstTri[0] = cv::Point2f(img.cols * 0.f, img.rows * 0.33f);
  dstTri[1] = cv::Point2f(img.cols * 0.85f, img.rows * 0.25f);
  dstTri[2] = cv::Point2f(img.cols * 0.15f, img.rows * 0.7f);
  cv::Mat warp_mat = cv::getAffineTransform(srcTri, dstTri);
  for (auto _ : state) {
    cv::Mat warp_dst;
    cv::warpAffine(img, warp_dst, warp_mat, img.size());
    benchmark::DoNotOptimize(warp_dst.data);
    benchmark::ClobberMemory();
  }
}

BENCHMARK_MAIN();
