#pragma once

#include <QTimer>

#include <igd/Application.h>

#include <gum/async/TaskQueue.h>

namespace ui {

class UiContext {
    igd::app::Application   _application;

    QTimer                  _mainTick;
    gum::TaskQueueRef       _taskQueue;

public:
    explicit UiContext();

    const igd::app::Application& getApplication() const {
        return _application;
    }

    gum::ITaskQueueRef getTaskQueue() const {
        return _taskQueue;
    }
};
GUM_DECLARE_REF(UiContext);
GUM_DECLARE_PTR(UiContext);

}
