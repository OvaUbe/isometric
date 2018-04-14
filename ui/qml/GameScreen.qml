import QtQuick 2.9

import Backend 1.0
import styles.LocationStyle 1.0
import styles.SurfaceTile 1.0
import styles.Wall 1.0

import "qrc:/qml/isometry" as Isometry

import "qrc:/qml/js/MathUtils.js" as MathUtils

Flickable {
    contentHeight: surfaceView.height
    contentWidth: surfaceView.width

    rightMargin: 3 * surfaceView.cellWidth
    leftMargin: 3 * surfaceView.cellWidth
    topMargin: 3 * surfaceView.cellHeight
    bottomMargin: 3 * surfaceView.cellHeight

    Isometry.SurfaceView {
        id: surfaceView

        forwardAngle: 60
        sideAngle: 45
        cellSide: 100

        levelHeight: 30
        maximumWallLevel: 6

        anchors.centerIn: parent

        model: Backend.environment.surfaceModel

        delegate: Item {
            property int row: surfaceView.computeCellRow(index)
            property int column: surfaceView.computeCellColumn(index)

            x: calculateX()
            y: calculateY()
            onXChanged: x = Qt.binding(calculateX)
            onYChanged: y = Qt.binding(calculateY)

            function calculateX() {
                return surfaceView.computeCellX(row, column)
            }

            function calculateY() {
                return surfaceView.computeCellY(row, column)
            }

            SurfaceTile {
                y: model.display ? -surfaceView.computeCellHeight(model.level) : 0

                visible: model.display ? true : false
                materialName: model.display ? model.materialName : ""

                panelSide: surfaceView.cellSide

                forwardAngle: surfaceView.forwardAngle
                sideAngle: surfaceView.sideAngle
            }

            Wall {
                y: surfaceView.computeLeftWallY(wallHeight)
                x: surfaceView.computeLeftWallX(height)

                visible: wallHeight !== 0
                materialName: model.display ? model.materialName : ""

                wallHeight: model.display ? surfaceView.computeCellHeight(model.level) : 0
                panelSide: surfaceView.leftWallTopSide
                angleBetweenSides: MathUtils.toDegrees(surfaceView.leftWallSideAngleRadians)
            }

            Wall {
                y: surfaceView.computeRightWallY(wallHeight)
                x: surfaceView.computeRightWallX(height)

                visible: wallHeight !== 0
                materialName: model.display ? model.materialName : ""

                wallHeight: model.display ? surfaceView.computeCellHeight(model.level) : 0
                panelSide: surfaceView.rightWallTopSide
                angleBetweenSides: MathUtils.toDegrees(surfaceView.rightWallSideAngleRadians)
            }
        }
    }

    Keys.onPressed: {
        if (event.modifiers & Qt.ControlModifier) {
            if (event.key === Qt.Key_Left)
                surfaceView.sideAngle = Math.max(surfaceView.sideAngle - 1, 0);
            else if (event.key === Qt.Key_Right)
                surfaceView.sideAngle = Math.min(surfaceView.sideAngle + 1, 90);
            else if (event.key === Qt.Key_Down)
                surfaceView.forwardAngle = Math.max(surfaceView.forwardAngle - 1, 0);
            else if (event.key === Qt.Key_Up)
                surfaceView.forwardAngle = Math.min(surfaceView.forwardAngle + 1, 90);
        }
    }
}
