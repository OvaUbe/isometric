import QtQuick 2.9

import Backend 1.0
import styles.LocationStyle 1.0
import styles.SurfaceTile 1.0
import styles.Wall 1.0

import "qrc:/qml/isometry" as Isometry
import "qrc:/qml/components" as Components

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

            property int wallHeight: surfaceView.computeCellHeight(model.level)

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

            Components.Optional {
                initialized: model.display !== undefined

                source: "qrc:/qml/styles/" + Backend.settings.chosenApplicationStyle + "/SurfaceTile.qml"
                properties: {
                    "y": Qt.binding(function() { return -surfaceView.computeCellHeight(model.level); }),
                    "materialName": Qt.binding(function() { return model.materialName; }),
                    "panelSide": Qt.binding(function() { return surfaceView.cellSide; }),
                    "forwardAngle": Qt.binding(function() { return surfaceView.forwardAngle; }),
                    "sideAngle": Qt.binding(function() { return surfaceView.sideAngle; })
                }
            }

            Components.Optional {
                initialized: (model.display !== undefined) && (wallHeight !== 0)

                source: "qrc:/qml/styles/" + Backend.settings.chosenApplicationStyle + "/Wall.qml"
                properties: {
                    "y": Qt.binding(function() { return surfaceView.computeLeftWallY(wallHeight); }),
                    "x": Qt.binding(function() { return surfaceView.computeLeftWallX(height); }),

                    "materialName": Qt.binding(function() { return model.materialName; }),

                    "wallHeight": Qt.binding(function() { return wallHeight; }),
                    "panelSide": Qt.binding(function() { return surfaceView.leftWallTopSide; }),
                    "angleBetweenSides": Qt.binding(function() { return MathUtils.toDegrees(surfaceView.leftWallSideAngleRadians); })
                }
            }

            Components.Optional {
                initialized: (model.display !== undefined) && (wallHeight !== 0)

                source: "qrc:/qml/styles/" + Backend.settings.chosenApplicationStyle + "/Wall.qml"
                properties: {
                    "y": Qt.binding(function() { return surfaceView.computeRightWallY(wallHeight); }),
                    "x": Qt.binding(function() { return surfaceView.computeRightWallX(height); }),

                    "materialName": Qt.binding(function() { return model.materialName; }),

                    "wallHeight": Qt.binding(function() { return wallHeight; }),
                    "panelSide": Qt.binding(function() { return surfaceView.rightWallTopSide; }),
                    "angleBetweenSides": Qt.binding(function() { return MathUtils.toDegrees(surfaceView.rightWallSideAngleRadians); })
                }
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
