

#pragma once

extern "C" {
// Seems to be missing C++ guards
#include "mrcal.h"

} // extern "C"

#include <span>
#include <vector>

class mrcal_result {
public:
  bool success;
  std::vector<double> intrinsics;
  double rms_error;
  std::vector<double> residuals;
  // TODO standard devs
};

#include <opencv2/opencv.hpp>

mrcal_pose_t getSeedPose(const mrcal_point3_t *c_observations_board_pool, cv::Size boardSize,
            cv::Size imagerSize, double squareSize, double focal_len_guess);

mrcal_result mrcal_main(
    // List, depth is ordered array observation[N frames, object_height,
    // object_width] = [x,y, weight] weight<0 means ignored)
    std::span<mrcal_point3_t> observations_board,
    // RT transform from camera to object
    std::span<mrcal_pose_t> frames_rt_toref,
    // Chessboard size, in corners (not squares)
    cv::Size calobjectSize, double boardSpacing,
    // res, pixels
    cv::Size cameraRes);
