#include <igd/Application.h>

#include <igd/Launcher.h>

namespace igd {
namespace app {

struct Application::Impl {
    ILauncherRef launcher;

public:
    Impl()
        :   launcher(gum::make_shared_ref<Launcher>()) { }
};


Application::Application()
    :   _impl(gum::make_unique_ref<Impl>()) { }


Application::~Application() { }


ILauncherRef Application::getLauncher() const {
    return _impl->launcher;
}

}
}
