#include <igd/application/Application.hxx>

#include <igd/application/Environment.hxx>
#include <igd/application/Launcher.hxx>

#include <gum/concurrency/Worker.h>

namespace igd {
namespace app {

Application::Application()
    : _worker(gum::make_shared_ref<gum::Worker>("igd")) {
    _environment = gum::make_shared_ref<Environment>(*this);
    _launcher = gum::make_shared_ref<Launcher>(*this);
}
}
}
