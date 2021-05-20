#include "skeletonization.h"

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>

using namespace cv;

void thinningIteration(Mat& im, int iter)
{
    Mat marker = Mat::zeros(im.size(), CV_8UC1);

    for (int i = 1; i < im.rows-1; i++)
    {
        for (int j = 1; j < im.cols-1; j++)
        {
            uchar p2 = im.at<uchar>(i-1, j);
            uchar p3 = im.at<uchar>(i-1, j+1);
            uchar p4 = im.at<uchar>(i, j+1);
            uchar p5 = im.at<uchar>(i+1, j+1);
            uchar p6 = im.at<uchar>(i+1, j);
            uchar p7 = im.at<uchar>(i+1, j-1);
            uchar p8 = im.at<uchar>(i, j-1);
            uchar p9 = im.at<uchar>(i-1, j-1);

            int A  = (p2 == 0 && p3 == 1) + (p3 == 0 && p4 == 1) +
                     (p4 == 0 && p5 == 1) + (p5 == 0 && p6 == 1) +
                     (p6 == 0 && p7 == 1) + (p7 == 0 && p8 == 1) +
                     (p8 == 0 && p9 == 1) + (p9 == 0 && p2 == 1);
            int B  = p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9;
            int m1 = iter == 0 ? (p2 * p4 * p6) : (p2 * p4 * p8);
            int m2 = iter == 0 ? (p4 * p6 * p8) : (p2 * p6 * p8);

            if (A == 1 && (B >= 2 && B <= 6) && m1 == 0 && m2 == 0)
                marker.at<uchar>(i,j) = 1;
        }
    }

    im &= ~marker;
}

void thinning(Mat& im)
{
    im /= 255;

    Mat prev = Mat::zeros(im.size(), CV_8UC1);
    Mat diff;

    do {
        thinningIteration(im, 0);
        thinningIteration(im, 1);
        absdiff(im, prev, diff);
        im.copyTo(prev);
    }
    while (countNonZero(diff) > 0);

    for (int i = 0; i < im.rows; ++i)
    {
        im.at<uchar>(i, 0) = 0;
        im.at<uchar>(i, im.cols - 1) = 0;
    }
    for (int j = 1; j < im.cols - 1; ++j)
    {
        im.at<uchar>(0, j) = 0;
        im.at<uchar>(im.rows - 1, j) = 0;
    }

    im *= 255;
}

Mat skeletonization(Mat inputImage)
{
    if (inputImage.empty()) {
    	std::cout << "[WARNING] Inside skeletonization, nothing to skeletonize: image source is empty" << std::endl;
        return inputImage;
    }

    Mat outputImage;
    cvtColor(inputImage, outputImage, COLOR_BGR2GRAY);
    threshold(outputImage, outputImage, 0, 255, THRESH_BINARY+THRESH_OTSU);

    thinning(outputImage);

    return outputImage;
}
