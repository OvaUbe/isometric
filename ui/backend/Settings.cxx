#include <ui/backend/Settings.hxx>

#include <QQmlContext>

namespace ui {

Settings::Settings(QObject*) {
    GUM_THROW(gum::NotImplementedException());
}

Settings::Settings(const QQmlEngine& qmlEngine, const UiContextRef&) {
    qmlEngine.rootContext()->setContextProperty("global_backend_settings", this);
}
}
