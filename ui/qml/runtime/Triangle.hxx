#pragma once

#include <QQuickItem>
#include <QQuickPaintedItem>

namespace ui {

class Triangle : public QQuickPaintedItem {
    using Self = Triangle;

    Q_OBJECT

    Q_PROPERTY(int leftSide READ leftSide WRITE setLeftside NOTIFY leftSideChanged)
    Q_PROPERTY(int rightSide READ rightSide WRITE setRightside NOTIFY rightSideChanged)
    Q_PROPERTY(qreal angleBetweenSides READ angleBetweenSides WRITE setAnglebetweensides NOTIFY angleBetweenSidesChanged)

    Q_PROPERTY(int borderWidth READ borderWidth WRITE setBorderwidth NOTIFY borderWidthChanged)
    Q_PROPERTY(QColor borderColor READ borderColor WRITE setBordercolor NOTIFY borderColorChanged)

    Q_PROPERTY(QColor color READ color WRITE setColor NOTIFY colorChanged)

  private:
    int _leftSide;
    int _rightSide;
    qreal _angleBetweenSides;

    QPointF _upPoint;
    QPointF _leftPoint;
    QPointF _rightPoint;

    int _borderWidth;
    QColor _borderColor;

    QColor _color;

  public:
    Triangle(QQuickItem* parent = nullptr);

    Q_INVOKABLE int leftSide() const {
        return _leftSide;
    }

    Q_INVOKABLE int rightSide() const {
        return _rightSide;
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

    Q_INVOKABLE void setRightside(int rightSide) {
        if (_rightSide == rightSide)
            return;

        _rightSide = rightSide;
        emit rightSideChanged();
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
    void rightSideChanged();
    void angleBetweenSidesChanged();
    void borderWidthChanged();
    void borderColorChanged();
    void colorChanged();

  private:
    void onDimensionsChanged();
};
}
