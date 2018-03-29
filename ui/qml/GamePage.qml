import QtQuick 2.0
import QtQuick.Layouts 1.0
import QtQuick.Controls 1.0

import Backend 1.0

import "isometry" as Isometry

Rectangle {
    id: root

    color: "black"

    Flickable {
        contentHeight: surfaceViewFrame.height
        contentWidth: surfaceViewFrame.width

        anchors.fill: parent

        Rectangle {
            id: surfaceViewFrame

            property int margin: 3 * surfaceView.delegateSide

            color: root.color

            width: surfaceView.width + 2 * margin
            height: surfaceView.height + 2 * margin

            Isometry.SurfaceView {
                id: surfaceView

                forwardAngle: 60
                sideAngle: 45
                delegateSide: 100

                anchors.centerIn: parent

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
}
