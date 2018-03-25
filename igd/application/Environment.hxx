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

    using ISurfaceMapBundle = gum::IObservableMap<LocationId, IReadonlySurfaceMapRef>;
    GUM_DECLARE_REF(ISurfaceMapBundle);

    using ObservableSurfaceMap = gum::ObservableValue<IReadonlySurfaceMapPtr, gum::OwnerEquals>;

  private:
    static gum::Logger _logger;

    ILocationManagerRef _locationManager;

    ISurfaceMapBundleRef _surfaceMapBundle;
    gum::Optional<LocationId> _currentLocationId;
    ObservableSurfaceMap _currentSurfaceMap;

    gum::ITaskQueueRef _worker;

    gum::LifeToken _lifeToken;

    gum::TokenPool _locationTokens;
    gum::Token _locationBundleConnection;
    gum::Token _lifeTokenReleaser;

  public:
    Environment(const struct IApplication& application);

    gum::Token create() override;

    IReadonlySurfaceMapBundleRef getSurfaceMapBundle() const override {
        return _surfaceMapBundle;
    }

    gum::SignalHandle<CurrentSurfaceMapChangedSignature> currentSurfaceMapChanged() const override {
        return _currentSurfaceMap.changed();
    }

  private:
    void doCreate();

    void destroy();
    void doDestroy();

    void onLocationBundleChanged(gum::MapOp op, const LocationId& id, const ILocationRef& location);
};
}
}
