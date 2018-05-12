#include <igd/application/LocationManager.hxx>

#include <igd/application/IApplication.hxx>
#include <igd/environment/location/Location.hxx>

#include <gum/Match.h>
#include <gum/concurrency/Worker.h>
#include <gum/container/ObservableSortedMap.h>
#include <gum/string/ToString.h>

#include <functional>

namespace igd {
namespace app {

namespace {

gum::String locationIdToMapPath(const LocationId& locationId) {
    return gum::String() << "assets/maps/" << locationId << ".tmx";
}

using LocationBundle = gum::ObservableSortedMap<LocationId, ILocationRef>;

using namespace std::placeholders;
}

GUM_DEFINE_LOGGER(LocationManager);

LocationManager::LocationManager(const IApplication& application)
    : _locationBundle(gum::make_shared_ref<LocationBundle>())
    , _worker(application.getWorker())
    , _parserWorker(gum::make_shared_ref<gum::Worker>("tiledMapParser"))
    , _lifeTokenReleaser(gum::make_token<gum::FunctionToken>([this] { _lifeToken.release(); })) {}

gum::Token LocationManager::load(const LocationId& locationId) {
    _worker->push(gum::make_cancellable([this, locationId] { doLoad(locationId); }, _lifeToken));

    return gum::make_token<gum::FunctionToken>(gum::make_cancellable([this, locationId] { unload(locationId); }, _lifeToken));
}

void LocationManager::doLoad(const LocationId& locationId) {
    _logger.info() << "load(" << locationId << ")";

    TiledMapParser parser(_parserWorker, locationIdToMapPath(locationId));

    _tiledMapParserConnections[locationId] = parser.locationReady().connect(std::bind(&Self::onLocationReady, this, locationId, _1), _worker);
    _tiledMapParsers.emplace(locationId, std::move(parser));
}

void LocationManager::unload(const LocationId& locationId) {
    _worker->push(gum::make_cancellable([this, locationId] { doUnload(locationId); }, _lifeToken));
}

void LocationManager::doUnload(const LocationId& locationId) {
    _logger.info() << "unload(" << locationId << ")";

    _tiledMapParserConnections.erase(locationId);
    _tiledMapParsers.erase(locationId);
    _locationBundle->remove(locationId);
}

void LocationManager::onLocationReady(const LocationId& locationId, const TiledMapParser::LocationOrError& location) {
    _logger.info() << "onLocationReady(" << locationId << ")";

    gum::match(
        location,
        [&, this](const ILocationRef& location) { _locationBundle->set(locationId, location); },
        [&, this](const gum::ExceptionRef& ex) {
            _logger.error() << "Failed to load tiled map for '" << locationId << "': " << ex;

            unload(locationId);
        });
}
}
}
