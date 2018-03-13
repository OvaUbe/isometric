#include <igd/Launcher.h>

namespace igd {
namespace app {

GUM_DEFINE_LOGGER(Launcher);


Launcher::Launcher()
    :   _isGameActive(),
        _gameStatusChanged([this](const auto& slot){ slot(_isGameActive); }) { }


void Launcher::newGame() {
    _logger.info() << "newGame()";

    setGameActive(true);
}


void Launcher::quitGame() {
    _logger.info() << "quitGame()";

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
