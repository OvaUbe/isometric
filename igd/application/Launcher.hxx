#pragma once

#include <igd/application/IEnvironment.hxx>
#include <igd/application/ILauncher.hxx>

#include <gum/ObservableValue.h>

namespace igd {
namespace app {

class Launcher : public virtual ILauncher {
    static gum::Logger _logger;

    IEnvironmentRef _environment;

    gum::ObservableValue<bool> _isGameActive;

    gum::ITaskQueueRef _worker;

    gum::Token _environmentToken;
    gum::LifeToken _lifeToken;

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
