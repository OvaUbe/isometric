#pragma once

#include <eigen3/Eigen/Dense>

namespace igd {

template <int Size_>
using Size = Eigen::Matrix<size_t, Size_, 1>;

template <int Size_>
using Position = Eigen::Matrix<size_t, Size_, 1>;
}
