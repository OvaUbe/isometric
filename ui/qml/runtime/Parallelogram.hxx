#pragma once

#include <QQuickItem>
#include <QQuickPaintedItem>

namespace ui {

class Parallelogram : public QQuickPaintedItem {
    using Self = Parallelogram;

    Q_OBJECT

    Q_PROPERTY(int leftSide READ leftSide WRITE setLeftside NOTIFY leftSideChanged)
    Q_PROPERTY(int topSide READ topSide WRITE setTopSide NOTIFY topSideChanged)
    Q_PROPERTY(qreal angleBetweenSides READ angleBetweenSides WRITE setAnglebetweensides NOTIFY angleBetweenSidesChanged)

    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderwidth NOTIFY borderWidthChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBordercolor NOTIFY borderColorChanged)

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

  private:
    int _leftSide;
    int _topSide;
    qreal _angleBetweenSides;

    QPointF _topLeftPoint;
    QPointF _topRightPoint;
    QPointF _bottomLeftPoint;
    QPointF _bottomRightPoint;

    int _borderWidth;
    QColor _borderColor;

    QColor _color;

  public:
    Parallelogram(QQuickItem* parent = nullptr);

    Q_INVOKABLE int leftSide() const {
        return _leftSide;
    }

    Q_INVOKABLE int topSide() const {
        return _topSide;
    }

    Q_INVOKABLE qreal angleBetweenSides() const {
        return _angleBetweenSides;
    }

    Q_INVOKABLE int borderWidth() const {
        return _borderWidth;
    }

    Q_INVOKABLE QColor borderColor() const {
        return _borderColor;
    }

    Q_INVOKABLE QColor color() const {
        return _color;
    }

    Q_INVOKABLE void setLeftside(int leftSide) {
        if (_leftSide == leftSide)
            return;

        _leftSide = leftSide;
        emit leftSideChanged();
    }

    Q_INVOKABLE void setTopSide(int topSide) {
        if (_topSide == topSide)
            return;

        _topSide = topSide;
        emit topSideChanged();
    }

    Q_INVOKABLE void setAnglebetweensides(qreal angleBetweenSides) {
        if (_angleBetweenSides == angleBetweenSides)
            return;

        _angleBetweenSides = angleBetweenSides;
        emit angleBetweenSidesChanged();
    }

    Q_INVOKABLE void setBorderwidth(int borderWidth) {
        if (_borderWidth == borderWidth)
            return;

        _borderWidth = borderWidth;
        emit borderWidthChanged();
    }

    Q_INVOKABLE void setBordercolor(QColor borderColor) {
        if (_borderColor == borderColor)
            return;

        _borderColor = borderColor;
        emit borderColorChanged();
    }

    Q_INVOKABLE void setColor(QColor color) {
        if (_color == color)
            return;

        _color = color;
        emit colorChanged();
    }

    void paint(QPainter* painter) override;

  signals:
    void leftSideChanged();
    void topSideChanged();
    void angleBetweenSidesChanged();
    void borderWidthChanged();
    void borderColorChanged();
    void colorChanged();

  private:
    void onDimensionsChanged();
};
}
