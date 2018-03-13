#pragma once

#include <igd/ILauncher.h>

namespace igd {
namespace app {

class Launcher : public virtual ILauncher {
    static gum::Logger          _logger;

    bool                        _isGameActive;
    gum::Signal<void(bool)>     _gameStatusChanged;

public:
    Launcher();

    void newGame() override;
    void quitGame() override;

    gum::SignalHandle<void(bool)> gameStatusChanged() const override {
        return _gameStatusChanged.get_handle();
    }

private:
    void setGameActive(bool active);
};

}
}
