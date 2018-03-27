#pragma once

#include <igd/environment/location/ILocation.hxx>

namespace igd {

class Location : public virtual ILocation {
    ISurfaceMapRef _surfaceMap;

  public:
    Location(const ISurfaceMapRef& surfaceMap)
        : _surfaceMap(surfaceMap) {}

    IReadonlySurfaceMapRef getReadonlySurfaceMap() const override {
        return _surfaceMap;
    }

    ISurfaceMapRef getSurfaceMap() const override {
        return _surfaceMap;
    }
};
}
