#pragma once

#include <igd/application/IApplication.hxx>

#include <gum/async/ITaskQueue.h>

#include <QObject>

namespace ui {

class UiContext {
    igd::app::IApplicationRef _application;

    gum::ITaskQueueRef _worker;

  public:
    explicit UiContext(QObject* context);

    const igd::app::IApplication& getApplication() const {
        return *_application;
    }

    gum::ITaskQueueRef getWorker() const {
        return _worker;
    }
};
GUM_DECLARE_REF(UiContext);
GUM_DECLARE_PTR(UiContext);
}
