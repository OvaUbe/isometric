#pragma once

#include <igd/application/ILauncher.h>

namespace igd {
namespace app {

class Launcher : public virtual ILauncher {
    static gum::Logger          _logger;

    bool                        _isGameActive;
    gum::Signal<void(bool)>     _gameStatusChanged;

    gum::ITaskQueueRef          _worker;

    gum::LifeToken              _lifeToken;

public:
    Launcher(const struct IApplication& application);

    gum::Token startGame() override;

    gum::SignalHandle<void(bool)> gameStatusChanged() const override {
        return _gameStatusChanged.get_handle();
    }

private:
    void endGame();

    void setGameActive(bool active);
};

}
}
