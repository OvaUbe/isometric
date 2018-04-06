import QtQuick 2.9
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

import Backend 1.0
import styles.LocationStyle 1.0

import "components" as Components
import "isometry" as Isometry

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

            anchors.centerIn: parent

            model: Backend.environment.surfaceModel

            delegate: Isometry.SurfaceDelegate {
                property int row: surfaceView.computeCellRow(index)
                property int column: surfaceView.computeCellColumn(index)

                worldX: surfaceView.computeCellX(row, column)
                worldY: surfaceView.computeCellY(row, column)

                isHidden: model.display ? false : true
                materialName: model.display ? model.materialName : ""

                panelSide: surfaceView.cellSide

                forwardAngle: surfaceView.forwardAngle
                sideAngle: surfaceView.sideAngle
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
