import QtQuick 2.9

import styles.SurfaceTile 1.0

SurfaceTile {
    property int sideSize

    property int realX
    property int realY

    x: realX
    onXChanged: x = Qt.binding(function() { return realX; })
    y: realY
    onYChanged: y = Qt.binding(function() { return realY; })

    width: sideSize
    height: sideSize
}
