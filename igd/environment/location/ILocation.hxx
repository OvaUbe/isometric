#pragma once

#include <igd/environment/surface/ISurfaceMap.hxx>
#include <igd/environment/surface/ISurfaceSize.hxx>

namespace igd {

struct IReadonlyLocation {
    virtual ~IReadonlyLocation() {}

    virtual IReadonlySurfaceSizeRef getReadonlySurfaceSize() const = 0;
    virtual IReadonlySurfaceMapRef getReadonlySurfaceMap() const = 0;
};
GUM_DECLARE_PTR(IReadonlyLocation);
GUM_DECLARE_REF(IReadonlyLocation);

struct ILocation : public virtual IReadonlyLocation {
    virtual ISurfaceSizeRef getSurfaceSize() const = 0;
    virtual ISurfaceMapRef getSurfaceMap() const = 0;
};
GUM_DECLARE_PTR(ILocation);
GUM_DECLARE_REF(ILocation);
}
