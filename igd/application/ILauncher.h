#pragma once

#include <gum/async/Signal.h>

namespace igd {
namespace app {

struct ILauncher {
    virtual ~ILauncher() { }

    virtual gum::Token startGame() = 0;

    virtual gum::SignalHandle<void(bool)> gameStatusChanged() const = 0;
};
GUM_DECLARE_PTR(ILauncher);
GUM_DECLARE_REF(ILauncher);

}
}
