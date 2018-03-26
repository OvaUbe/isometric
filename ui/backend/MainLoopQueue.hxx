#pragma once

#include <gum/async/TaskQueue.h>

#include <QObject>

namespace ui {

class MainLoopQueue : public QObject, public virtual gum::ITaskQueue {
    Q_OBJECT

  private:
    gum::TaskQueue _wrapped;

  public:
    MainLoopQueue(QObject* context);

    void push(Task&& task) override;

  signals:
    void run();
};
}
