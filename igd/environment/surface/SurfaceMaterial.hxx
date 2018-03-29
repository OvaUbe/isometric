#pragma once

#include <gum/string/StringLiteral.h>

#include <boost/variant.hpp>

namespace igd {

namespace surface_materials {

#define IGD_DETAIL_DECLARE_SIMPLE_MATERIAL(Type_, Name_)                                                                                                       \
    struct Type_ {                                                                                                                                             \
        gum::StringLiteral getName() const {                                                                                                                   \
            return Name_;                                                                                                                                      \
        }                                                                                                                                                      \
    }

IGD_DETAIL_DECLARE_SIMPLE_MATERIAL(Steel, "steel");
IGD_DETAIL_DECLARE_SIMPLE_MATERIAL(CeramicTile, "ceramicTile");
IGD_DETAIL_DECLARE_SIMPLE_MATERIAL(Concrete, "concrete");

#undef IGD_DETAIL_DECLARE_SIMPLE_MATERIAL
}

using SurfaceMaterial = boost::variant<surface_materials::Steel, surface_materials::CeramicTile, surface_materials::Concrete>;
}
