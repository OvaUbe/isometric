#pragma once

#include <igd/application/ILocationManager.hxx>

#include <gum/log/Logger.h>

namespace igd {
namespace app {

class LocationManager : public virtual ILocationManager {
    using ILocationBundle = gum::IObservableMap<LocationId, ILocationRef>;
    GUM_DECLARE_REF(ILocationBundle);

  public:
    static gum::Logger _logger;

    ILocationBundleRef _locationBundle;

    gum::ITaskQueueRef _worker;

    gum::LifeToken _lifeToken;

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
};
GUM_DECLARE_PTR(ILocationManager);
GUM_DECLARE_REF(ILocationManager);
}
}
