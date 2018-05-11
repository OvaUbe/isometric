#pragma once

#include <gum/log/Logger.h>

#include <QString>

namespace ui {

class TypeRegistrator {
    static gum::Logger _logger;

  public:
    TypeRegistrator(const QString& chosenStyle);
};
}
