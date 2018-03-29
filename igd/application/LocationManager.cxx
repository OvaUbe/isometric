#include <igd/application/LocationManager.hxx>

#include <igd/application/IApplication.hxx>

#include <gum/container/ObservableSortedMap.h>

namespace igd {
namespace app {

namespace {

using LocationBundle = gum::ObservableSortedMap<LocationId, ILocationRef>;
}

GUM_DEFINE_LOGGER(LocationManager);

LocationManager::LocationManager(const IApplication& application)
    : _locationBundle(gum::make_shared_ref<LocationBundle>())
    , _worker(application.getWorker()) {}

gum::Token LocationManager::load(const LocationId& locationId) {
    _worker->push(gum::make_cancellable([this, locationId] { doLoad(locationId); }, _lifeToken.get_handle()));

    return gum::make_token<gum::FunctionToken>(gum::make_cancellable([this, locationId] { unload(locationId); }, _lifeToken.get_handle()));
}

void LocationManager::doLoad(const LocationId& locationId) {
    _logger.info() << "load(" << locationId << ")";
}

void LocationManager::unload(const LocationId& locationId) {
    _worker->push(gum::make_cancellable([this, locationId] { doUnload(locationId); }, _lifeToken.get_handle()));
}

void LocationManager::doUnload(const LocationId& locationId) {
    _logger.info() << "unload(" << locationId << ")";
}
}
}
