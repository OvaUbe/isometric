#pragma once

#include <igd/environment/surface/SurfaceMaterial.hxx>

#include <gum/Optional.h>
#include <gum/smartpointer/SharedPtr.h>
#include <gum/smartpointer/SharedReference.h>

namespace igd {

struct ISurfaceUnit {
    virtual ~ISurfaceUnit() {}

    virtual const SurfaceMaterial& getMaterial() const = 0;
    virtual gum::Optional<size_t> getLevel() const = 0;
};
GUM_DECLARE_PTR(ISurfaceUnit);
GUM_DECLARE_REF(ISurfaceUnit);
}
