#include <igd/application/Launcher.h>

namespace igd {
namespace app {

GUM_DEFINE_LOGGER(Launcher);


Launcher::Launcher()
    :   _isGameActive(),
        _gameStatusChanged([this](const auto& slot){ slot(_isGameActive); }) { }


gum::Token Launcher::startGame() {
    _logger.info() << "startGame()";

    setGameActive(true);

    return gum::make_token<gum::FunctionToken>(gum::make_cancellable([this]{ endGame(); }, _lifeToken.get_handle()));
}


void Launcher::endGame() {
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
