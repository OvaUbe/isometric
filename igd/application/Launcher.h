#pragma once

#include <igd/application/ILauncher.h>

#include <gum/ObservableValue.h>

namespace igd {
namespace app {

class Launcher : public virtual ILauncher {
    static gum::Logger                          _logger;

    gum::ObservableValue<bool>                  _isGameActive;

    gum::ITaskQueueRef                          _worker;

    gum::LifeToken                              _lifeToken;

public:
    Launcher(const struct IApplication& application);

    gum::Token startGame() override;

    gum::SignalHandle<GameStatusChangedSignature> gameStatusChanged() const override {
        return _isGameActive.changed();
    }

private:
    void doStartGame();

    void endGame();
    void doEndGame();
};

}
}
