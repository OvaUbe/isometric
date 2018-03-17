#pragma once

#include <igd/environment/surface/ISurfaceUnit.hxx>
#include <igd/environment/surface/SurfaceDescriptor.hxx>

#include <gum/container/IObservableMap.h>

namespace igd {

using IReadonlySurfaceMap = gum::IReadonlyObservableMap<SurfaceDescriptor, ISurfaceUnitRef>;
GUM_DECLARE_PTR(IReadonlySurfaceMap);
GUM_DECLARE_REF(IReadonlySurfaceMap);

using ISurfaceMap = gum::IObservableMap<SurfaceDescriptor, ISurfaceUnitRef>;
GUM_DECLARE_PTR(ISurfaceMap);
GUM_DECLARE_REF(ISurfaceMap);

}
