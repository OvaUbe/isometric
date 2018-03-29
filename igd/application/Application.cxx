#include <igd/application/Application.hxx>

#include <igd/application/Environment.hxx>
#include <igd/application/Launcher.hxx>
#include <igd/application/LocationManager.hxx>

#include <gum/concurrency/Worker.h>

namespace igd {
namespace app {

Application::Application()
    : _worker(gum::make_shared_ref<gum::Worker>("igd")) {
    _locationManager = gum::make_shared_ref<LocationManager>(*this);
    _environment = gum::make_shared_ref<Environment>(*this);
    _launcher = gum::make_shared_ref<Launcher>(*this);
}
}
}
