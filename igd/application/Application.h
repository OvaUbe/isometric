#pragma once

#include <igd/application/IApplication.h>

namespace igd {
namespace app {

class Application : public virtual IApplication {
    gum::ITaskQueueRef      _worker;

    ILauncherRef            _launcher;

public:
    Application();

    gum::ITaskQueueRef getWorker() const override {
        return _worker;
    }

    ILauncherRef getLauncher() const override {
        return _launcher;
    }
};

}
}
