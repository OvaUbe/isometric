import QtQuick 2.9

Loader {
    property bool initialized

    property string source
    property var properties

    onInitializedChanged: {
        if (initialized)
            setSource(source, properties)
        else
            source = ""
    }
}
