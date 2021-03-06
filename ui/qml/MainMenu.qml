import QtQuick 2.9
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2

import Backend 1.0

Rectangle {
    ColumnLayout {
        anchors.centerIn: parent

        Button {
            text: "New Game"

            onClicked: Backend.launcher.newGame()
        }

        Button { text: "Settings" }

        Button {
            text: "Exit"

            onClicked: Qt.quit()
        }
    }
}
