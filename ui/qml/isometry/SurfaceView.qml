import QtQuick 2.9

GridView {
    property real forwardAngle
    property real sideAngle
    property int cellSide

    property int levelHeight
    property int maximumWallLevel

    function toRadians(angle) {
        return angle * (Math.PI / 180);
    }

    property int maximumWallHeight: levelHeight * maximumWallLevel

    property real forwardAngleRadians: toRadians(forwardAngle)
    property real sideAngleRadians: toRadians(sideAngle)

    property real cellRightWidth: cellSide * Math.sin(sideAngleRadians)
    property real cellLeftWidth: cellSide * Math.cos(sideAngleRadians)
    property real cellTopHeight: cellLeftWidth * Math.cos(forwardAngleRadians)
    property real cellBottomHeight: cellRightWidth * Math.cos(forwardAngleRadians)

    property int leftWidth: cellRightWidth * model.tableRowCount
    property int rightWidth: cellLeftWidth * model.tableColumnCount

    function computeCellRow(index) {
        return (model.tableColumnCount !== 0) ? Math.floor(index / model.tableColumnCount) : 0
    }

    function computeCellColumn(index) {
        return (model.tableColumnCount !== 0) ? Math.floor(index % model.tableColumnCount) : 0
    }

    function computeCellX(row, column) {
        return (leftWidth - row * cellRightWidth) + (column * cellLeftWidth);
    }

    function computeCellY(row, column) {
        return maximumWallHeight + row * cellTopHeight + column * cellBottomHeight;
    }

    function computeCellHeight(level) {
        return (levelHeight * ((level !== undefined) ? level : maximumWallLevel)) * Math.sin(forwardAngleRadians)
    }

    cellWidth: cellRightWidth + cellLeftWidth
    cellHeight: cellTopHeight + cellBottomHeight

    width: leftWidth + rightWidth
    height: maximumWallHeight + cellTopHeight * model.tableRowCount + cellBottomHeight * model.tableColumnCount
}
