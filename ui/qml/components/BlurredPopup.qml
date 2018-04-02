import QtQuick 2.9
import QtQuick.Layouts 1.0
import QtQuick.Controls 2.2
import QtGraphicalEffects 1.0

Popup {
    id: popup

    property int blur: 0

    padding: 0.0

    modal: true

    background: Item {
        ShaderEffectSource {
            id: effectSource

            anchors.fill: parent

            sourceItem: popup.parent
            sourceRect: Qt.rect(popup.x, popup.y, popup.width, popup.height)
        }
        FastBlur {
            anchors.fill: effectSource

            source: effectSource
            radius: popup.blur
        }
    }
}
