import QtQuick 2.0

import styles.debug.LocationStyle 1.0
import "qrc:/qml/isometry" as Isometry

Isometry.Wall {
    property string materialName

    color: "white"

    borderColor: "black"
    borderWidth: 2

    Text { text: materialName }
}
