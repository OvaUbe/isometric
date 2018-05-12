import QtQuick 2.9
import QtQuick.Window 2.1

import Backend 1.0

Rectangle {
    id: mainWindow

    width: Window.width
    height: Window.height

    Loader {
        id: pageLoader

        anchors.fill: parent

        asynchronous: true

        source: Backend.launcher.isGameActive ? "GamePage.qml" : "MainMenu.qml"
    }
}
