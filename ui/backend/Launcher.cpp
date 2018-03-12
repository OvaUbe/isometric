#include <ui/backend/Launcher.h>

#include <QQmlContext>

namespace ui {

Launcher::Launcher(QObject* parent)
    :   QObject(parent) { }


Launcher::Launcher(const QQmlEngine& qmlEngine, const UiContextRef& uiContext)
    :   _uiContext(uiContext) {
    qmlEngine.rootContext()->setContextProperty("global_backend_launcher", this);
}


void Launcher::newGame() { }

}
