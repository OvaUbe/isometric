#pragma once

#include <QTimer>

#include <igd/Application.h>

#include <gum/async/ITaskQueue.h>

namespace ui {

class UiContext {
    igd::app::Application   _application;

    QTimer                  _mainTick;
    gum::ITaskQueueRef      _worker;

public:
    explicit UiContext();

    const igd::app::Application& getApplication() const {
        return _application;
    }

    gum::ITaskQueueRef getWorker() const {
        return _worker;
    }
};
GUM_DECLARE_REF(UiContext);
GUM_DECLARE_PTR(UiContext);

}
