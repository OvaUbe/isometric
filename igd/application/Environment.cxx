#include <igd/application/Environment.hxx>

#include <igd/application/IApplication.hxx>

#include <gum/container/ObservableSortedMap.h>

namespace igd {
namespace app {

namespace {

using SurfaceMapBundle = gum::ObservableSortedMap<LocationId, IReadonlySurfaceMapRef>;
}

GUM_DEFINE_LOGGER(Environment);

Environment::Environment(const IApplication& application)
    : _surfaceMapBundle(gum::make_shared_ref<SurfaceMapBundle>())
    , _worker(application.getWorker()) {}

gum::Token Environment::create() {
    _worker->push(gum::make_cancellable([this] { doCreate(); }, _lifeToken.get_handle()));

    return gum::make_token<gum::FunctionToken>(gum::make_cancellable([this] { destroy(); }, _lifeToken.get_handle()));
}

void Environment::doCreate() {
    _logger.info() << "create()";
}

void Environment::destroy() {
    _worker->push(gum::make_cancellable([this] { doDestroy(); }, _lifeToken.get_handle()));
}

void Environment::doDestroy() {
    _logger.info() << "destroy()";

    _currentSurfaceMap = nullptr;
    _surfaceMapBundle->clear();
}
}
}
