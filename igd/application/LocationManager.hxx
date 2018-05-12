#pragma once

#include <igd/application/ILocationManager.hxx>
#include <igd/environment/tiled/TiledMapParser.hxx>

#include <gum/log/Logger.h>

#include <map>

namespace igd {
namespace app {

class LocationManager : public virtual ILocationManager {
    using Self = LocationManager;

    using ILocationBundle = gum::IObservableMap<LocationId, ILocationRef>;
    GUM_DECLARE_REF(ILocationBundle);

    using TiledMapParsers = std::map<LocationId, TiledMapParser>;

    using TiledMapParserConnections = std::map<LocationId, gum::Token>;

  public:
    static gum::Logger _logger;

    ILocationBundleRef _locationBundle;
    TiledMapParsers _tiledMapParsers;

    gum::ITaskQueueRef _worker;
    gum::ITaskQueueRef _parserWorker;

    gum::LifeToken _lifeToken;

    TiledMapParserConnections _tiledMapParserConnections;
    gum::Token _lifeTokenReleaser;

  public:
    LocationManager(const struct IApplication& application);

    gum::Token load(const LocationId& locationId) override;

    IReadonlyLocationBundleRef getLocationBundle() const override {
        return _locationBundle;
    }

  private:
    void doLoad(const LocationId& locationId);

    void unload(const LocationId& locationId);
    void doUnload(const LocationId& locationId);

    void onLocationReady(const LocationId& locationId, const TiledMapParser::LocationOrError& location);
};
GUM_DECLARE_PTR(ILocationManager);
GUM_DECLARE_REF(ILocationManager);
}
}
