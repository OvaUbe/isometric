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
        contentHeight: surfaceViewFrame.height
        contentWidth: surfaceViewFrame.width

        anchors.fill: parent

        Rectangle {
            id: surfaceViewFrame

            property int margin: 3 * surfaceView.cellSide

            color: root.color

            width: surfaceView.width + 2 * margin
            height: surfaceView.height + 2 * margin

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

                    isHidden: display ? false : true
                    materialName: display ? display : ""

                    forwardAngle: surfaceView.forwardAngle
                    sideAngle: surfaceView.sideAngle

                    sideSize: surfaceView.cellSide

                    realX: surfaceView.computeCellX(row, column)
                    realY: surfaceView.computeCellY(row, column)
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
