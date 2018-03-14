#pragma once

#include <igd/application/ILauncher.h>

namespace igd {
namespace app {

struct IApplication {
    virtual ~IApplication() { }

    virtual gum::ITaskQueueRef getWorker() const = 0;

    virtual ILauncherRef getLauncher() const = 0;
};
GUM_DECLARE_REF(IApplication);

}
}
