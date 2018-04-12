import QtQuick 2.9

import "qrc:/qml/js/MathUtils.js" as MathUtils

GridView {
    property real forwardAngle
    property real sideAngle
    property int cellSide

    property int levelHeight
    property int maximumWallLevel

    property int maximumWallHeight: levelHeight * maximumWallLevel

    property real forwardAngleRadians: MathUtils.toRadians(forwardAngle)
    property real sideAngleRadians: MathUtils.toRadians(sideAngle)

    property real cellRightWidth: cellSide * Math.sin(sideAngleRadians)
    property real cellLeftWidth: cellSide * Math.cos(sideAngleRadians)
    property real cellTopHeight: cellLeftWidth * Math.cos(forwardAngleRadians)
    property real cellBottomHeight: cellRightWidth * Math.cos(forwardAngleRadians)

    property int leftWidth: cellRightWidth * model.tableRowCount
    property int rightWidth: cellLeftWidth * model.tableColumnCount

    property int leftWallTopSide: Math.sqrt(Math.pow(cellLeftWidth, 2) + Math.pow(cellBottomHeight, 2))
    property int rightWallTopSide: Math.sqrt(Math.pow(cellRightWidth, 2) + Math.pow(cellTopHeight, 2))

    property real leftWallSideAngleRadians: Math.PI - ((Math.PI / 2) - (cellLeftWidth ? Math.atan(cellBottomHeight / cellLeftWidth) : 0))
    property real rightWallSideAngleRadians: (Math.PI / 2) - (cellRightWidth ? Math.atan(cellTopHeight / cellRightWidth) : 0)

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

    function computeLeftWallX(wallWidth) {
        return wallWidth - (cellWidth / 2 - cellSide / 2);
    }

    function computeLeftWallY(wallHeight) {
        return -wallHeight - (cellHeight / 2 - cellSide / 2) + cellTopHeight;
    }

    function computeRightWallX(wallWidth) {
        return wallWidth - (cellWidth / 2 - cellSide / 2) + cellLeftWidth;
    }

    function computeRightWallY(wallHeight) {
        return -wallHeight - (cellHeight / 2 - cellSide / 2) + cellBottomHeight;
    }

    cellWidth: cellRightWidth + cellLeftWidth
    cellHeight: cellTopHeight + cellBottomHeight

    width: leftWidth + rightWidth
    height: maximumWallHeight + cellTopHeight * model.tableRowCount + cellBottomHeight * model.tableColumnCount
}
