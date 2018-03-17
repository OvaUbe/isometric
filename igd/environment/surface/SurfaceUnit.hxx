#pragma once

#include <igd/environment/surface/ISurfaceUnit.h>

namespace igd {

class SurfaceUnit : public virtual ISurfaceUnit {
    SurfaceMaterial _material;

public:
    SurfaceUnit(SurfaceMaterial&& materual)
        :   _material(std::move(materual)) { }

    const SurfaceMaterial& getMaterial() const override {
        return _material;
    }
};

}
