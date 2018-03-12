import QtQuick 2.0

Rectangle {
    id: mainWindow

    width: 1024
    height: 768

    Loader {
        id: pageLoader

        anchors.fill: parent

        asynchronous: true

        source: "MainMenu.qml"
    }
}
