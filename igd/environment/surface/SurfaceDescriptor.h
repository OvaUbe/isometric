#pragma once

#include <gum/Types.h>

namespace igd {

struct SurfaceDescriptor {
    gum::u32 x;
    gum::u32 y;

public:
    SurfaceDescriptor(gum::u32 x_, gum::u32 y_)
        :   x(x_),
            y(y_)
    { }
};

}
