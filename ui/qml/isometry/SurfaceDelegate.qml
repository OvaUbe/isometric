import QtQuick 2.9

import styles.SurfaceTile 1.0

SurfaceTile {
    property int worldX
    property int worldY

    x: worldX
    y: worldY
    onXChanged: x = Qt.binding(function() { return worldX; })
    onYChanged: y = Qt.binding(function() { return worldY; })
}
