#include <igd/application/Environment.hxx>

#include <igd/application/IApplication.hxx>
#include <igd/core/Core.hxx>

#include <gum/container/ObservableSortedMap.h>
#include <gum/maybe/Maybe.h>

#include <functional>

namespace igd {
namespace app {

namespace {

using LocationBundle = gum::ObservableSortedMap<LocationId, IReadonlyLocationRef>;

using namespace std::placeholders;
}

GUM_DEFINE_LOGGER(Environment);

Environment::Environment(const IApplication& application)
    : _locationManager(application.getLocationManager())
    , _locationBundle(gum::make_shared_ref<LocationBundle>())
    , _worker(application.getWorker())
    , _lifeTokenReleaser(gum::make_token<gum::FunctionToken>([this] { _lifeToken.release(); })) {}

gum::Token Environment::create() {
    _worker->push(gum::make_cancellable([this] { doCreate(); }, _lifeToken));

    return gum::make_token<gum::FunctionToken>(gum::make_cancellable([this] { destroy(); }, _lifeToken));
}

void Environment::doCreate() {
    _logger.info() << "create()";

    _currentLocationId = "entrance";
    _locationTokens += _locationManager->load(*_currentLocationId);
    _locationBundleConnection = _locationManager->getLocationBundle()->changed().connect(std::bind(&Self::onLocationBundleChanged, this, _1, _2, _3), _worker);
}

void Environment::destroy() {
    _worker->push(gum::make_cancellable([this] { doDestroy(); }, _lifeToken));
}

void Environment::doDestroy() {
    _logger.info() << "destroy()";

    _locationBundleConnection.release();
    _locationTokens.reset();

    _currentLocationId.reset();
    _currentLocation = null;
    _locationBundle->clear();
}

void Environment::onLocationBundleChanged(gum::MapOp op, const LocationId& id, const ILocationRef& location) {
    const bool isCurrentLocationId = _currentLocationId && *_currentLocationId == id;

    switch (op) {
    case gum::MapOp::Added:
    case gum::MapOp::Updated:
        _locationBundle->set(id, location);
        if (isCurrentLocationId)
            _currentLocation = location;
        break;
    case gum::MapOp::Removed:
        _locationBundle->remove(id);
        if (isCurrentLocationId)
            _currentLocation = null;
        break;
    }
}
}
}
