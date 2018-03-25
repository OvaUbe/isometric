#pragma once

#include <igd/environment/location/ILocation.hxx>

namespace igd {

class Location : public virtual ILocation {
    ISurfaceMapRef _surfaceMap;

  public:
    Location(const ISurfaceMapRef& surfaceMap)
        : _surfaceMap(surfaceMap) {}

    ISurfaceMapRef getSurfaceMap() const {
        return _surfaceMap;
    }
};
}
