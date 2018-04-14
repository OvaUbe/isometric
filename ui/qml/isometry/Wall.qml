import QtQuick 2.9

import "qrc:/qml/components" as Components

Components.Parallelogram {
    property int wallHeight
    property int panelSide
    property int perspectiveAngle

    topSide: wallHeight
    leftSide: panelSide

    transform: Rotation {
        origin.x: 0
        origin.y: 0
        axis { x: 0; y: 0; z: 1 } angle: 90
    }
}
