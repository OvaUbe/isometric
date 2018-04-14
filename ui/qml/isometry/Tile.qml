import QtQuick 2.9

Rectangle {
    id: isometricTile

    property int panelSide

    property real forwardAngle
    property real sideAngle

    width: panelSide
    height: panelSide

    transform: [
        Rotation {
            origin.x: isometricTile.width / 2
            origin.y: isometricTile.height / 2
            axis { x: 0; y: 0; z: 1 } angle: isometricTile.sideAngle
        },
        Rotation {
            origin.x: isometricTile.width / 2
            origin.y: isometricTile.height / 2
            axis { x: 1; y: 0; z: 0 } angle: isometricTile.forwardAngle
        }
    ]
}
