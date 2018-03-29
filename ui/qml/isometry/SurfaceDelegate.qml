import QtQuick 2.9

import "." as Isometry

Isometry.Tile {
    property int sideSize: 0
    property int tableColumnCount: 0

    function toRadians(angle) {
        return angle * (Math.PI / 180);
    }

    property real forwardAngleRadians: toRadians(forwardAngle)
    property real sideAngleRadians: toRadians(sideAngle)

    property int cellWidth: sideSize / Math.cos(sideAngleRadians)

    property bool isOddRow: (Math.floor(model.index / tableColumnCount) % 2) == 1
    property int isometricOffset: isOddRow ? (cellWidth / 2) : 0
    property int positionInARow: model.index % tableColumnCount

    width: sideSize
    height: sideSize

    property bool preventRecursiveXUpdate: true
    function setX() {
        var savedPreventRecursiveXUpdate = preventRecursiveXUpdate
        preventRecursiveXUpdate = !preventRecursiveXUpdate
        if (savedPreventRecursiveXUpdate)
            x = positionInARow * cellWidth + isometricOffset
    }

    onXChanged: setX()

    Component.onCompleted: setX()
}
