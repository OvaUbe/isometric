#include <ui/backend/UiContext.h>

#include <gum/async/TaskQueue.h>

namespace ui {

namespace {

gum::ITaskQueueRef createTaskQueue(const QTimer& mainTick) {
    const gum::TaskQueueRef taskQueue = gum::make_shared_ref<gum::TaskQueue>();
    QObject::connect(&mainTick, &QTimer::timeout, [=]{ taskQueue->run(); });
    return taskQueue;
}

}


UiContext::UiContext()
    :   _taskQueue(createTaskQueue(_mainTick)) {
    _mainTick.start();
}

}
