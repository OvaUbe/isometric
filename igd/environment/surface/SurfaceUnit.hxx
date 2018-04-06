#pragma once

#include <igd/environment/surface/ISurfaceUnit.hxx>

namespace igd {

class SurfaceUnit : public virtual ISurfaceUnit {
    SurfaceMaterial _material;
    gum::Optional<size_t> _level;

  public:
    SurfaceUnit(SurfaceMaterial&& material, const gum::Optional<size_t>& level = (size_t)0)
        : _material(std::move(material))
        , _level(level) {}

    const SurfaceMaterial& getMaterial() const override {
        return _material;
    }

    gum::Optional<size_t> getLevel() const override {
        return _level;
    }
};
}
