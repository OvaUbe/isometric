import QtQuick 2.0

import styles.debug.LocationStyle 1.0
import "qrc:/qml/isometry" as Isometry

Isometry.Tile {
    property bool isHidden
    property string materialName

    color: isHidden ? LocationStyle.spaceColor : "white"

    border.color: "black"
    border.width: 2

    Text { text: materialName }
}
