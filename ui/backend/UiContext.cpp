#include <ui/backend/UiContext.h>

namespace ui {

UiContext::UiContext()
    :   _taskQueue(gum::make_shared_ref<gum::TaskQueue>()) {
    _mainTick.start();
    QObject::connect(&_mainTick, &QTimer::timeout, [taskQueue=_taskQueue]{ taskQueue->run(); });
}

}
