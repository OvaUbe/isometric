import QtQuick 2.9

import "." as Isometry

Isometry.Tile {
    property int sideSize
    property int row
    property int column
    property int cellWidth
    property int cellHeight

    function toRadians(angle) {
        return angle * (Math.PI / 180);
    }

    property real forwardAngleRadians: toRadians(forwardAngle)
    property real sideAngleRadians: toRadians(sideAngle)

    property bool isOddRow: (row % 2) == 1
    property int isometricOffset: isOddRow ? (cellWidth / 2) : 0

    width: sideSize
    height: sideSize

    property bool preventRecursiveXUpdate: true
    function setX() {
        var savedPreventRecursiveXUpdate = preventRecursiveXUpdate
        preventRecursiveXUpdate = !preventRecursiveXUpdate
        if (savedPreventRecursiveXUpdate)
            x = column * cellWidth + isometricOffset
    }

    onXChanged: setX()

    Component.onCompleted: setX()
}
