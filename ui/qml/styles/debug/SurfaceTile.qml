import QtQuick 2.0

import styles.debug.LocationStyle 1.0
import "qrc:/qml/isometry" as Isometry

Isometry.Tile {
    property string materialName

    color: "white"

    border.color: "black"
    border.width: 2

    Text { text: materialName }
}
