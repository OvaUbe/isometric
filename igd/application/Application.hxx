#pragma once

#include <igd/application/IApplication.hxx>

namespace igd {
namespace app {

class Application : public virtual IApplication {
    gum::ITaskQueueRef _worker;

    ILocationManagerPtr _locationManager;
    IEnvironmentPtr _environment;
    ILauncherPtr _launcher;

  public:
    Application();

    ILocationManagerRef getLocationManager() const override {
        return _locationManager;
    }

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
