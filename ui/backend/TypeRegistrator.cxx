#include <ui/backend/TypeRegistrator.hxx>

#include <ui/backend/Environment.hxx>
#include <ui/backend/Launcher.hxx>

#include <QQmlEngine>

namespace ui {

TypeRegistrator::TypeRegistrator() {
    qmlRegisterSingletonType(QUrl("qrc:/qml/Backend.qml"), "Backend", 1, 0, "Backend");

    qmlRegisterSingletonType(QUrl("qrc:/qml/styles/debug/LocationStyle.qml"), "styles.debug.LocationStyle", 1, 0, "LocationStyle");
    qmlRegisterType(QUrl("qrc:/qml/styles/debug/SurfaceTile.qml"), "styles.debug.SurfaceTile", 1, 0, "SurfaceTile");

    qmlRegisterSingletonType(QUrl("qrc:/qml/styles/debug/LocationStyle.qml"), "styles.LocationStyle", 1, 0, "LocationStyle");
    qmlRegisterType(QUrl("qrc:/qml/styles/debug/SurfaceTile.qml"), "styles.SurfaceTile", 1, 0, "SurfaceTile");

    qmlRegisterType<ui::Launcher>("ui.backend.launcher", 1, 0, "Launcher");
    qmlRegisterType<ui::Environment>("ui.backend.environment", 1, 0, "Environment");
}
}
