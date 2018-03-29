import QtQuick 2.9

GridView {
    property real forwardAngle: 0
    property real sideAngle: 0
    property int delegateSide: 0

    function toRadians(angle) {
        return angle * (Math.PI / 180);
    }

    property real forwardAngleRadians: toRadians(forwardAngle)
    property real sideAngleRadians: toRadians(sideAngle)

    cellWidth: delegateSide / Math.cos(sideAngleRadians)
    cellHeight: (cellWidth / 2) * Math.cos(forwardAngleRadians)
}
