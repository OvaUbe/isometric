#pragma once

#include <igd/environment/location/ILocation.hxx>
#include <igd/environment/location/LocationId.hxx>

#include <gum/container/IObservableMap.h>

namespace igd {
namespace app {

struct ILocationManager {
    using IReadonlyLocationBundle = gum::IReadonlyObservableMap<LocationId, ILocationRef>;
    GUM_DECLARE_REF(IReadonlyLocationBundle);

  public:
    virtual ~ILocationManager() {}

    virtual gum::Token load(const LocationId& locationId) = 0;

    virtual IReadonlyLocationBundleRef getLocationBundle() const = 0;
};
GUM_DECLARE_PTR(ILocationManager);
GUM_DECLARE_REF(ILocationManager);
}
}
