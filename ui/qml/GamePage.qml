import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

import Backend 1.0

import "isometry" as Isometry

Rectangle {
    id: root

    color: "black"

    Flickable {
        contentHeight: surfaceView.height
        contentWidth: surfaceView.width

        anchors.fill: parent

        Isometry.SurfaceView {
            id: surfaceView

            forwardAngle: 60
            sideAngle: 45
            delegateSide: 100

            width: model.tableColumnCount * cellWidth
            height: model.tableRowCount * cellHeight

            model: Backend.environment.surfaceModel

            delegate: Isometry.SurfaceDelegate {
                forwardAngle: surfaceView.forwardAngle
                sideAngle: surfaceView.sideAngle

                sideSize: surfaceView.delegateSide
                tableColumnCount: surfaceView.model.tableColumnCount

                color: display ? "white" : "black"

                border.color: "black"
                border.width: 2

                Text { text: "Material:\n" + display }
            }
        }
    }
}
