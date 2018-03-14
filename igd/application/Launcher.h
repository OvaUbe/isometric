#pragma once

#include <igd/application/ILauncher.h>

namespace igd {
namespace app {

class Launcher : public virtual ILauncher {
    static gum::Logger                          _logger;

    bool                                        _isGameActive;
    gum::Signal<GameStatusChangedSignature>     _gameStatusChanged;

    gum::ITaskQueueRef                          _worker;

    gum::LifeToken                              _lifeToken;

public:
    Launcher(const struct IApplication& application);

    gum::Token startGame() override;

    gum::SignalHandle<GameStatusChangedSignature> gameStatusChanged() const override {
        return _gameStatusChanged.get_handle();
    }

private:
    void doStartGame();

    void endGame();
    void doEndGame();

    void setGameActive(bool active);
};

}
}
