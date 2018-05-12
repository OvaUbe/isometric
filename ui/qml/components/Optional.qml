import QtQuick 2.9

Loader {
    property bool initialized

    property string source
    property var properties

    asynchronous: true

    onInitializedChanged: {
        if (initialized)
            setSource(source, bindProperties());
        else
            sourceComponent = undefined;
    }

    function bindProperties() {
        return Object.keys(properties).reduce(function(accumulator, key) {
            accumulator[key] = Qt.binding(function() { return properties[key]; });
            return accumulator;
        }, {});
    }
}
