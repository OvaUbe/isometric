import QtQuick 2.9

import Backend 1.0

Rectangle {
    id: mainWindow

    width: 1024
    height: 768

    Loader {
        id: pageLoader

        anchors.fill: parent

        asynchronous: false

        source: Backend.launcher.isGameActive ? "GamePage.qml" : "MainMenu.qml"
    }
}
