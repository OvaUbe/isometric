import QtQuick 2.9
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

import Backend 1.0
import styles.LocationStyle 1.0
import styles.SurfaceTile 1.0

import "qrc:/qml/components" as Components
import "qrc:/qml/isometry" as Isometry

Rectangle {
    id: root

    focus: true

    color: LocationStyle.spaceColor

    Flickable {
        contentHeight: surfaceView.height
        contentWidth: surfaceView.width

        anchors.fill: parent

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

                    isHidden: model.display ? false : true
                    materialName: model.display ? model.materialName : ""

                    panelSide: surfaceView.cellSide

                    forwardAngle: surfaceView.forwardAngle
                    sideAngle: surfaceView.sideAngle
                }
            }
        }
    }

    Components.BlurredPopup {
        id: menuPopup

        width: parent.width
        height: parent.height

        blur: 20

        contentItem: ColumnLayout {
            anchors.fill: parent

            Label {
                text: '<b>Isometric</b>'

                Layout.alignment: Qt.AlignCenter
            }
            Button {
                text: 'Quit to menu'

                Layout.alignment: Qt.AlignCenter

                onClicked: Backend.launcher.quitGame()
            }
        }
    }

    Keys.onEscapePressed: menuPopup.visible = !menuPopup.visible
}
