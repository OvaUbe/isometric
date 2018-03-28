#pragma once

#include <igd/core/Geometry.hxx>

#include <gum/IObservableValue.h>

namespace igd {

using SurfaceSize = Size<2>;

using IReadonlySurfaceSize = gum::IReadonlyObservableValue<SurfaceSize>;
GUM_DECLARE_REF(IReadonlySurfaceSize);

using ISurfaceSize = gum::IObservableValue<SurfaceSize>;
GUM_DECLARE_REF(ISurfaceSize);
}
