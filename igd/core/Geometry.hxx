#pragma once

#include <eigen3/Eigen/Dense>

namespace igd {

template <size_t Size_>
using Size = Eigen::Matrix<size_t, Size_, 1>;

template <size_t Size_>
using Position = Eigen::Matrix<size_t, Size_, 1>;
}
