#pragma once

#include <igd/application/IEnvironment.hxx>
#include <igd/application/ILauncher.hxx>
#include <igd/application/ILocationManager.hxx>

namespace igd {
namespace app {

struct IApplication {
    virtual ~IApplication() {}

    virtual gum::ITaskQueueRef getWorker() const = 0;

    virtual ILocationManagerRef getLocationManager() const = 0;
    virtual IEnvironmentRef getEnvironment() const = 0;
    virtual ILauncherRef getLauncher() const = 0;
};
GUM_DECLARE_REF(IApplication);
}
}
