#pragma once

#include <igd/core/Core.hxx>
#include <igd/core/Geometry.hxx>
#include <igd/environment/surface/SurfaceMaterial.hxx>

#include <gum/Optional.h>
#include <gum/smartpointer/SharedPtr.h>
#include <gum/smartpointer/SharedReference.h>

namespace igd {

struct TileInfo {
    gum::String TilesetPath;
    Position<2> TileId;
    u32 TileSide;

  public:
    TileInfo(const gum::String& tilesetPath, const Position<2>& tileId, const u32 tileSide)
        : TilesetPath(tilesetPath)
        , TileId(tileId)
        , TileSide(tileSide) {}
};

struct ISurfaceUnit {
    virtual ~ISurfaceUnit() {}

    virtual const SurfaceMaterial& getMaterial() const = 0;
    virtual const TileInfo& getTileInfo() const = 0;
    virtual gum::Optional<size_t> getLevel() const = 0;
};
GUM_DECLARE_PTR(ISurfaceUnit);
GUM_DECLARE_REF(ISurfaceUnit);
}
