#pragma once

#include <igd/core/Geometry.hxx>

#include <gum/Range.h>
#include <gum/string/ToString.h>

namespace gum {

template <typename Unit_, size_t Rows_, size_t Columns_>
struct StringRepresentableTrait<Eigen::Matrix<Unit_, Rows_, Columns_>, std::enable_if_t<Columns_ != 1>> : std::true_type {
    static String to_string(const Eigen::Matrix<Unit_, Rows_, Columns_>& matrix) {
        String result;

        result << "[";
        for (auto row : range<size_t>(0, Rows_)) {
            result << "[";
            for (auto column : range<size_t>(0, Columns_)) {
                result << matrix(row, column);
                if (column != (Columns_ - 1))
                    result << ", ";
            }
            result << "]";

            if (row != (Rows_ - 1))
                result << ", ";
        }
        result << "]";

        return result;
    }
};

template <typename Unit_, size_t Rows_, size_t Columns_>
struct StringRepresentableTrait<Eigen::Matrix<Unit_, Rows_, Columns_>, std::enable_if_t<Columns_ == 1>> : std::true_type {
    static String to_string(const Eigen::Matrix<Unit_, Rows_, Columns_>& matrix) {
        String result;

        result << "[";
        for (auto row : range<size_t>(0, Rows_)) {
            result << matrix[row];
            if (row != (Rows_ - 1))
                result << ", ";
        }
        result << "]";

        return result;
    }
};
}
