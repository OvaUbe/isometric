#pragma once

#include <gum/async/Signal.h>

namespace igd {
namespace app {

struct ILauncher {
    using GameStatusChangedSignature = void(bool);

public:
    virtual ~ILauncher() { }

    virtual gum::Token startGame() = 0;

    virtual gum::SignalHandle<GameStatusChangedSignature> gameStatusChanged() const = 0;
};
GUM_DECLARE_PTR(ILauncher);
GUM_DECLARE_REF(ILauncher);

}
}
