#pragma once

#include <igd/environment/location/ILocation.hxx>

#include <gum/ObservableValue.h>

namespace igd {

class Location : public virtual ILocation {
    using ObservableSurfaceSize = gum::ObservableValue<SurfaceSize>;

  private:
    ISurfaceSizeRef _surfaceSize;
    ISurfaceMapRef _surfaceMap;

  public:
    Location(const SurfaceSize& surfaceSize, const ISurfaceMapRef& surfaceMap)
        : _surfaceSize(gum::make_shared_ref<ObservableSurfaceSize>(surfaceSize))
        , _surfaceMap(surfaceMap) {}

    IReadonlySurfaceSizeRef getReadonlySurfaceSize() const override {
        return _surfaceSize;
    }

    IReadonlySurfaceMapRef getReadonlySurfaceMap() const override {
        return _surfaceMap;
    }

    ISurfaceSizeRef getSurfaceSize() const override {
        return _surfaceSize;
    }

    ISurfaceMapRef getSurfaceMap() const override {
        return _surfaceMap;
    }
};
}
