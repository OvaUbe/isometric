#pragma once

#include <QTimer>

#include <gum/async/TaskQueue.h>

namespace ui {

class UiContext {
    QTimer                  _mainTick;
    gum::TaskQueueRef       _taskQueue;

public:
    explicit UiContext();

    gum::ITaskQueueRef getTaskQueue() const {
        return _taskQueue;
    }
};
GUM_DECLARE_REF(UiContext);
GUM_DECLARE_PTR(UiContext);

}
