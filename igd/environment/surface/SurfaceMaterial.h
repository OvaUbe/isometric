#pragma once

#include <boost/variant.hpp>

namespace igd {

namespace surface_materials {

struct Steel { };

struct CeramicTile { };

struct Concrete { };

}

using SurfaceMaterial = boost::variant<
        surface_materials::Steel,
        surface_materials::CeramicTile,
        surface_materials::Concrete
    >;

}
