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

    property real cellLeftWidth: cellSide * Math.sin(sideAngleRadians)
    property real cellRightWidth: cellSide * Math.cos(sideAngleRadians)
    property real cellTopHeight: cellRightWidth * Math.cos(forwardAngleRadians)
    property real cellBottomHeight: cellLeftWidth * Math.cos(forwardAngleRadians)

    property int leftWidth: cellLeftWidth * model.tableRowCount
    property int rightWidth: cellRightWidth * model.tableColumnCount

    function computeCellRow(index) {
        return (model.tableColumnCount !== 0) ? Math.floor(index / model.tableColumnCount) : 0
    }

    function computeCellColumn(index) {
        return (model.tableColumnCount !== 0) ? Math.floor(index % model.tableColumnCount) : 0
    }

    function computeCellX(row, column) {
        return (leftWidth - row * cellLeftWidth) + (column * cellRightWidth);
    }

    function computeCellY(row, column) {
        return maximumWallHeight + row * cellTopHeight + column * cellBottomHeight;
    }

    function computeCellHeight(level) {
        return (levelHeight * ((level !== undefined) ? level : maximumWallLevel)) * Math.sin(forwardAngleRadians)
    }

    cellWidth: cellLeftWidth + cellRightWidth
    cellHeight: cellTopHeight + cellBottomHeight

    width: leftWidth + rightWidth
    height: maximumWallHeight + cellTopHeight * model.tableRowCount + cellBottomHeight * model.tableColumnCount
}
