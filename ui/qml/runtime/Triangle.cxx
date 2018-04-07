#include <ui/qml/runtime/Triangle.hxx>

#include <ui/core/math/Geometry.hxx>

#include <QPainter>
#include <QPainterPathStroker>

namespace ui {

Triangle::Triangle(QQuickItem* parent)
    : QQuickPaintedItem(parent)
    , _leftSide()
    , _rightSide()
    , _angleBetweenSides()
    , _borderWidth() {
    QObject::connect(this, &Self::leftSideChanged, [this] { onDimensionsChanged(); });
    QObject::connect(this, &Self::rightSideChanged, [this] { onDimensionsChanged(); });
    QObject::connect(this, &Self::angleBetweenSidesChanged, [this] { onDimensionsChanged(); });
}

void Triangle::paint(QPainter* painter) {
    QPainterPath background;
    background.moveTo(_leftPoint);
    background.lineTo(_upPoint);
    background.lineTo(_rightPoint);
    background.lineTo(_leftPoint);

    const QPainterPathStroker stroker(QPen(_borderColor, _borderWidth));
    const QPainterPath border = stroker.createStroke(background).intersected(background);

    painter->fillPath(background, _color);
    painter->fillPath(border, _borderColor);
}

void Triangle::onDimensionsChanged() {
    const qreal width = triangleSide(_leftSide, _rightSide, qDegreesToRadians(_angleBetweenSides));
    const qreal area = heronArea(_leftSide, _rightSide, width);
    const qreal height = (width != 0.) ? (2 * area / width) : 0;
    const qreal upPointX = qSqrt(qPow(_leftSide, 2) - qPow(height, 2));

    _leftPoint = QPointF(0, height);
    _rightPoint = QPointF(width, height);
    _upPoint = QPointF(upPointX, 0);

    setWidth(width);
    setHeight(height);
}
}
