#include <ui/backend/TypeRegistrator.hxx>

#include <ui/backend/Environment.hxx>
#include <ui/backend/Launcher.hxx>

#include <QQmlEngine>

namespace ui {

TypeRegistrator::TypeRegistrator() {
    qmlRegisterSingletonType(QUrl("qrc:/qml/Backend.qml"), "Backend", 1, 0, "Backend");
    qmlRegisterType<ui::Launcher>("ui.backend.launcher", 1, 0, "Launcher");
    qmlRegisterType<ui::Environment>("ui.backend.environment", 1, 0, "Environment");
}
}
