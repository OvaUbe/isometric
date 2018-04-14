#pragma once

#include <QtCore>

namespace ui {

inline qreal heronArea(qreal a, qreal b, qreal c) {
    const qreal s = (a + b + c) / 2;
    return qSqrt(s * (s - a) * (s - b) * (s - c));
}

inline qreal triangleSide(qreal lhs, qreal rhs, qreal angle) {
    return qSqrt(qPow(lhs, 2) + qPow(rhs, 2) - (2 * lhs * rhs * qCos(angle)));
}
}
