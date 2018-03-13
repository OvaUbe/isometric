#include <ui/backend/Launcher.h>

#include <QQmlContext>

#include <functional>

namespace ui {

using namespace std::placeholders;


Launcher::Launcher(QObject* parent)
    :   QObject(parent) { }


Launcher::Launcher(const QQmlEngine& qmlEngine, const UiContextRef& uiContext)
    :   _uiContext(uiContext),
        _isGameActive() {
    qmlEngine.rootContext()->setContextProperty("global_backend_launcher", this);

    _launcherConnection = _uiContext->getApplication().getLauncher()->gameStatusChanged().connect(std::bind(&Self::OnGameStatusChanged, this, _1), _uiContext->getTaskQueue());
}


void Launcher::newGame() {
    _uiContext->getApplication().getLauncher()->newGame();
}


void Launcher::quitGame() {
    _uiContext->getApplication().getLauncher()->quitGame();
}


void Launcher::OnGameStatusChanged(bool status) {
    if (_isGameActive == status)
        return;

    _isGameActive = status;
    emit gameStatusChanged();
}

}
