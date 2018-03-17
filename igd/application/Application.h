#pragma once

#include <igd/application/IApplication.h>

namespace igd {
namespace app {

class Application : public virtual IApplication {
    gum::ITaskQueueRef      _worker;

    IEnvironmentPtr         _environment;
    ILauncherPtr            _launcher;

public:
    Application();

    gum::ITaskQueueRef getWorker() const override {
        return _worker;
    }

    IEnvironmentRef getEnvironment() const override {
        return _environment;
    }

    ILauncherRef getLauncher() const override {
        return _launcher;
    }
};

}
}
