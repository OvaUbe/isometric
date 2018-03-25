#pragma once

#include <igd/environment/location/LocationId.hxx>
#include <igd/environment/surface/ISurfaceMap.hxx>

namespace igd {
namespace app {

struct IEnvironment {
    using IReadonlySurfaceMapBundle = gum::IReadonlyObservableMap<LocationId, IReadonlySurfaceMapRef>;
    GUM_DECLARE_REF(IReadonlySurfaceMapBundle);

    using CurrentSurfaceMapChangedSignature = void(const IReadonlySurfaceMapPtr&);

  public:
    virtual ~IEnvironment() {}

    virtual gum::Token create() = 0;

    virtual IReadonlySurfaceMapBundleRef getSurfaceMapBundle() const = 0;

    virtual gum::SignalHandle<CurrentSurfaceMapChangedSignature> currentSurfaceMapChanged() const = 0;
};
GUM_DECLARE_PTR(IEnvironment);
GUM_DECLARE_REF(IEnvironment);
}
}
