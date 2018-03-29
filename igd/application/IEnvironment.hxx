#pragma once

#include <igd/environment/location/ILocation.hxx>
#include <igd/environment/location/LocationId.hxx>

namespace igd {
namespace app {

struct IEnvironment {
    using IReadonlyLocationBundle = gum::IReadonlyObservableMap<LocationId, IReadonlyLocationRef>;
    GUM_DECLARE_REF(IReadonlyLocationBundle);

    using CurrentLocationChangedSignature = void(const IReadonlyLocationPtr&);

  public:
    virtual ~IEnvironment() {}

    virtual gum::Token create() = 0;

    virtual IReadonlyLocationBundleRef getLocationBundle() const = 0;

    virtual gum::SignalHandle<CurrentLocationChangedSignature> currentLocationChanged() const = 0;
};
GUM_DECLARE_PTR(IEnvironment);
GUM_DECLARE_REF(IEnvironment);
}
}
