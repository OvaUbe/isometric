pragma Singleton

import QtQuick 2.9
import backend.Launcher 1.0
import backend.Environment 1.0
import backend.Settings 1.0

Item {
    property var launcher: global_backend_launcher
    property var environment: global_backend_environment
    property var settings: global_backend_settings
}
