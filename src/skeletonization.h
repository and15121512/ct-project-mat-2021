#ifndef SKELETONIZATION_HPP
#define SKELETONIZATION_HPP

#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace cv;

/**
 * Perform one thinning iteration.
 * Normally you wouldn't call this function directly from your code.
 */
void thinningIteration(Mat& im, int iter);

/**
 * Function for thinning the given binary image
 */
void thinning(Mat& im);

/**
 * This is the function that acts as the input/output system of this header file.
 */
Mat skeletonization(Mat inputImage);

#endif // #ifndef SKELETONIZATION_HPP
