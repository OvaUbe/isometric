import QtQuick 2.9

import styles.SurfaceTile 1.0

SurfaceTile {
    property int worldX
    property int worldY

    property int tileHeight

    x: calculateX()
    y: calculateY()
    onXChanged: x = Qt.binding(calculateX)
    onYChanged: y = Qt.binding(calculateY)

    function calculateX() {
        return worldX
    }

    function calculateY() {
        return worldY - tileHeight
    }
}
