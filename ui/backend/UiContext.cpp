#include <ui/backend/UiContext.h>

#include <gum/async/TaskQueue.h>

namespace ui {

namespace {

gum::ITaskQueueRef createWorker(const QTimer& mainTick) {
    const gum::TaskQueueRef worker = gum::make_shared_ref<gum::TaskQueue>();
    QObject::connect(&mainTick, &QTimer::timeout, [=]{ worker->run(); });
    return worker;
}

}


UiContext::UiContext()
    :   _worker(createWorker(_mainTick)) {
    _mainTick.start();
}

}
