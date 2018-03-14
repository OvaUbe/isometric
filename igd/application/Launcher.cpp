#include <igd/application/Launcher.h>

#include <igd/application/IApplication.h>

namespace igd {
namespace app {

GUM_DEFINE_LOGGER(Launcher);


Launcher::Launcher(const IApplication& application)
    :   _isGameActive(),
        _gameStatusChanged([this](const auto& slot){ slot(_isGameActive); }),
        _worker(application.getWorker()) { }


gum::Token Launcher::startGame() {
    _worker->push(gum::make_cancellable([this]{ doStartGame(); }, _lifeToken.get_handle()));

    return gum::make_token<gum::FunctionToken>(gum::make_cancellable([this]{ endGame(); }, _lifeToken.get_handle()));
}


void Launcher::doStartGame() {
    _logger.info() << "startGame()";

    setGameActive(true);
}


void Launcher::endGame() {
    _worker->push(gum::make_cancellable([this]{ doEndGame(); }, _lifeToken.get_handle()));
}


void Launcher::doEndGame() {
    _logger.info() << "endGame()";

    setGameActive(false);
}


void Launcher::setGameActive(bool active) {
    gum::SignalLock l(_gameStatusChanged.get_mutex());

    if (_isGameActive == active)
        return;

    _isGameActive = active;
    _gameStatusChanged(_isGameActive);
}

}
}
