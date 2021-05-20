#include "skeletonization.h"

#include <opencv2/opencv.hpp>

#include <iostream>
#include <filesystem>

using namespace cv;

int main(int argc, char** argv)
{
    if (3 != argc)
    {
        std::cout << "[ERROR] One argument required: input image path, output dir." << std::endl;
        return 0;
    }

    std::filesystem::path in_file = std::filesystem::path(argv[1]).lexically_normal();
    std::filesystem::path out_dir = std::filesystem::path(argv[2]).lexically_normal();
    std::filesystem::path out_skel = out_dir / ("skel_" + in_file.filename().string());
    std::filesystem::path out_merged = out_dir / ("merged_" + in_file.filename().string());

    Mat im = cv::imread(in_file.string());
    if (im.empty()) {
        std::cout << "[ERROR] Can't open input image: " + in_file.string() << std::endl;
        return 0;
    }
    Mat skel = skeletonization(im);
    cv::imwrite(out_skel.string(), skel);

    skel = cv::imread(out_skel.string());
    if (skel.empty()) {
        std::cout << "[ERROR] Can't save output skel image: " + out_skel.string() << std::endl;
        return 0;
    }
    cv::Mat merged;
    cv::bitwise_and(im, ~skel, merged);
    cv::bitwise_or(skel - Scalar(0, 255, 255), merged, merged);
    cv::imwrite(out_merged.string(), merged);

    return 0;
}
