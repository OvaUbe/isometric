import QtQuick 2.0

import "qrc:/qml/isometry" as Isometry

Isometry.Tile {
    property string materialName

    property string tilesetPath
    property point tileId
    property int tileSide

    Item {
        width: tileSide
        height: tileSide

        clip: true

        transform: Scale {
            xScale: panelSide / tileSide
            yScale: panelSide / tileSide
        }

        Image {
            x: -(tileId.x * tileSide)
            y: -(tileId.y * tileSide)

            asynchronous: true

            source: "/assets/maps/" + tilesetPath
        }
    }
}
