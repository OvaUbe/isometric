#pragma once

#include <igd/application/ILauncher.h>

namespace igd {
namespace app {

struct Application {
    struct Impl;
    GUM_DECLARE_UNIQUE_REF(Impl);

private:
    ImplUniqueRef _impl;

public:
    Application();
    ~Application();

    gum::ITaskQueueRef getWorker() const;

    ILauncherRef getLauncher() const;
};

}
}
