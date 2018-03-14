#include <igd/Application.h>

#include <igd/Launcher.h>

#include <gum/concurrency/Worker.h>

namespace igd {
namespace app {

struct Application::Impl {
    gum::ITaskQueueRef      worker;
    ILauncherRef            launcher;

public:
    Impl()
        :   worker(gum::make_shared_ref<gum::Worker>("igd")),
            launcher(gum::make_shared_ref<Launcher>()) { }
};


Application::Application()
    :   _impl(gum::make_unique_ref<Impl>()) { }


Application::~Application() { }


gum::ITaskQueueRef Application::getWorker() const {
    return _impl->worker;
}


ILauncherRef Application::getLauncher() const {
    return _impl->launcher;
}

}
}
