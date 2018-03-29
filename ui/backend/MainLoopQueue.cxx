#include <ui/backend/MainLoopQueue.hxx>

namespace ui {

MainLoopQueue::MainLoopQueue(QObject* context) {
    QObject::connect(this, &MainLoopQueue::run, context, [this] { _wrapped.run(); }, Qt::QueuedConnection);
}

void MainLoopQueue::push(Task&& task) {
    _wrapped.push(std::move(task));
    emit run();
}
}
