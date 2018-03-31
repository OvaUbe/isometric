import QtQuick 2.9

import styles.SurfaceTile 1.0

SurfaceTile {
    id: isometricTile

    property real forwardAngle
    property real sideAngle

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
