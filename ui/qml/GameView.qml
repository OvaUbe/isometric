import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

import Backend 1.0

Rectangle {
    ColumnLayout {
        anchors.left: parent.left

        Button { text: "Settings" }

        Button {
            text: "Quit to Main Menu"

            onClicked: Backend.launcher.quitGame()
        }
    }
}
