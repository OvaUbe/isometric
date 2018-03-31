#pragma once

#include <gum/string/ToString.h>

#include <QString>

namespace gum {

template <>
struct StringRepresentableTrait<QString> : std::true_type {
    static String to_string(const QString& str) {
        String result;
        result.reserve(str.size());
        for (const auto qchar : str)
            result.push_back(qchar.toLatin1());
        return result;
    }
};
}
