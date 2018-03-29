#pragma once

#include <igd/application/IEnvironment.hxx>
#include <igd/application/ILocationManager.hxx>
#include <igd/environment/surface/ISurfaceMap.hxx>

#include <gum/ObservableValue.h>
#include <gum/token/TokenPool.h>

namespace igd {
namespace app {

class Environment : public virtual IEnvironment {
    using Self = Environment;

    using ILocationBundle = gum::IObservableMap<LocationId, IReadonlyLocationRef>;
    GUM_DECLARE_REF(ILocationBundle);

    using ObservableLocation = gum::ObservableValue<IReadonlyLocationPtr, gum::OwnerEquals>;

  private:
    static gum::Logger _logger;

    ILocationManagerRef _locationManager;

    ILocationBundleRef _locationBundle;
    gum::Optional<LocationId> _currentLocationId;
    ObservableLocation _currentLocation;

    gum::ITaskQueueRef _worker;

    gum::LifeToken _lifeToken;

    gum::TokenPool _locationTokens;
    gum::Token _locationBundleConnection;
    gum::Token _lifeTokenReleaser;

  public:
    Environment(const struct IApplication& application);

    gum::Token create() override;

    IReadonlyLocationBundleRef getLocationBundle() const override {
        return _locationBundle;
    }

    gum::SignalHandle<CurrentLocationChangedSignature> currentLocationChanged() const override {
        return _currentLocation.changed();
    }

  private:
    void doCreate();

    void destroy();
    void doDestroy();

    void onLocationBundleChanged(gum::MapOp op, const LocationId& id, const ILocationRef& location);
};
}
}
