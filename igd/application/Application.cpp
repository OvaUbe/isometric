#include <igd/application/Application.h>

#include <igd/application/Launcher.h>

#include <gum/concurrency/Worker.h>

namespace igd {
namespace app {

Application::Application()
    :   _worker(gum::make_shared_ref<gum::Worker>("igd")) {
    _launcher = gum::make_shared_ref<Launcher>(*this);
}

}
}
