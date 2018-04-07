#include <ui/qml/runtime/Parallelogram.hxx>

#include <ui/core/math/Geometry.hxx>

#include <QPainter>
#include <QPainterPathStroker>

#include <QDebug>

namespace ui {

Parallelogram::Parallelogram(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , _leftSide()
    , _topSide()
    , _angleBetweenSides()
    , _borderWidth() {
    QObject::connect(this, &Self::leftSideChanged, [this] { onDimensionsChanged(); });
    QObject::connect(this, &Self::topSideChanged, [this] { onDimensionsChanged(); });
    QObject::connect(this, &Self::angleBetweenSidesChanged, [this] { onDimensionsChanged(); });
}

void Parallelogram::paint(QPainter* painter) {
    QPainterPath background;
    background.moveTo(_topLeftPoint);
    background.lineTo(_topRightPoint);
    background.lineTo(_bottomRightPoint);
    background.lineTo(_bottomLeftPoint);
    background.lineTo(_topLeftPoint);

    const QPainterPathStroker stroker(QPen(_borderColor, _borderWidth));
    const QPainterPath border = stroker.createStroke(background).intersected(background);

    painter->fillPath(background, _color);
    painter->fillPath(border, _borderColor);
}

void Parallelogram::onDimensionsChanged() {
    const qreal diag = triangleSide(_leftSide, _topSide, qDegreesToRadians(_angleBetweenSides));
    const qreal half_area = heronArea(_leftSide, _topSide, diag);
    const qreal height = 2 * half_area / _topSide;
    const qreal bias = qSqrt(qPow(_leftSide, 2) - qPow(height, 2));
    const qreal width = _topSide + bias;
    const bool rightBaised = _angleBetweenSides > 90;
    const qreal topBias = rightBaised ? bias : 0;
    const qreal bottomBias = rightBaised ? 0 : bias;

    _topLeftPoint = QPointF(topBias, 0);
    _topRightPoint = QPointF(_topSide + topBias, 0);
    _bottomLeftPoint = QPointF(bottomBias, height);
    _bottomRightPoint = QPointF(_topSide + bottomBias, height);

    setWidth(width);
    setHeight(height);
}
}
