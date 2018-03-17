#include <igd/application/Launcher.hxx>

#include <igd/application/IApplication.hxx>

namespace igd {
namespace app {

GUM_DEFINE_LOGGER(Launcher);


Launcher::Launcher(const IApplication& application)
    :   _environment(application.getEnvironment()),
        _worker(application.getWorker()) { }


gum::Token Launcher::startGame() {
    _worker->push(gum::make_cancellable([this]{ doStartGame(); }, _lifeToken.get_handle()));

    return gum::make_token<gum::FunctionToken>(gum::make_cancellable([this]{ endGame(); }, _lifeToken.get_handle()));
}


void Launcher::doStartGame() {
    _logger.info() << "startGame()";

    _environmentToken = _environment->create();

    _isGameActive = true;
}


void Launcher::endGame() {
    _worker->push(gum::make_cancellable([this]{ doEndGame(); }, _lifeToken.get_handle()));
}


void Launcher::doEndGame() {
    _logger.info() << "endGame()";

    _environmentToken.release();

    _isGameActive = false;
}

}
}
