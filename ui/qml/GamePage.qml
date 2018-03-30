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

            property int margin: 3 * surfaceView.delegateSide

            color: root.color

            width: surfaceView.width + 2 * margin
            height: surfaceView.height + 2 * margin

            Isometry.SurfaceView {
                id: surfaceView

                forwardAngle: 60
                sideAngle: 45
                delegateSide: 100

                anchors.centerIn: parent

                width: model.tableColumnCount * cellWidth
                height: model.tableRowCount * cellHeight

                model: Backend.environment.surfaceModel

                delegate: Isometry.SurfaceDelegate {
                    isHidden: display ? false : true
                    materialName: display ? display : ""

                    forwardAngle: surfaceView.forwardAngle
                    sideAngle: surfaceView.sideAngle

                    sideSize: surfaceView.delegateSide
                    tableColumnCount: surfaceView.model.tableColumnCount
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
