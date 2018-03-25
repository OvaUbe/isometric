#pragma once

#include <igd/environment/surface/ISurfaceMap.hxx>

namespace igd {

struct ILocation {
    virtual ~ILocation() {}

    virtual ISurfaceMapRef getSurfaceMap() const = 0;
};
GUM_DECLARE_REF(ILocation);
}
