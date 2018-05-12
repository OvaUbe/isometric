#pragma once

#include <igd/environment/surface/ISurfaceUnit.hxx>

namespace igd {

class SurfaceUnit : public virtual ISurfaceUnit {
    SurfaceMaterial _material;
    TileInfo _tileInfo;
    gum::Optional<size_t> _level;

  public:
    SurfaceUnit(SurfaceMaterial&& material, TileInfo&& tileInfo, const gum::Optional<size_t>& level = (size_t)0)
        : _material(std::move(material))
        , _tileInfo(std::move(tileInfo))
        , _level(level) {}

    const SurfaceMaterial& getMaterial() const override {
        return _material;
    }

    const TileInfo& getTileInfo() const override {
        return _tileInfo;
    }

    gum::Optional<size_t> getLevel() const override {
        return _level;
    }
};
}
