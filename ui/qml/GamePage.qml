import QtQuick 2.9
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2

import Backend 1.0
import styles.LocationStyle 1.0

import "qrc:/qml/components" as Components
import "qrc:/qml" as Local

Rectangle {
    id: root

    focus: true

    color: LocationStyle.spaceColor

    Local.GameScreen {
        id: gameScreen

        anchors.fill: parent
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
    Keys.forwardTo: gameScreen
}
