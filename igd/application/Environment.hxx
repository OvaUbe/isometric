#pragma once

#include <igd/application/IEnvironment.hxx>

#include <igd/environment/surface/ISurfaceMap.hxx>

#include <gum/ObservableValue.h>

namespace igd {
namespace app {

class Environment : public virtual IEnvironment {
    using ISurfaceMapBundle = gum::IObservableMap<gum::String, IReadonlySurfaceMapRef>;
    GUM_DECLARE_REF(ISurfaceMapBundle);

    using ObservableSurfaceMap = gum::ObservableValue<IReadonlySurfaceMapPtr, gum::OwnerEquals>;

  private:
    static gum::Logger _logger;

    ISurfaceMapBundleRef _surfaceMapBundle;
    ObservableSurfaceMap _currentSurfaceMap;

    gum::ITaskQueueRef _worker;

    gum::LifeToken _lifeToken;

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
};
}
}
