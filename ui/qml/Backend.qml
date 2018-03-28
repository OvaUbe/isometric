pragma Singleton

import QtQuick 2.0
import ui.backend.launcher 1.0
import ui.backend.environment 1.0

Item {
    property var launcher: global_backend_launcher
    property var environment: global_backend_environment
}
