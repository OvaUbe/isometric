#include <ui/backend/UiContext.hxx>

#include <ui/backend/MainLoopQueue.hxx>

#include <igd/application/Application.hxx>

namespace ui {

UiContext::UiContext(QObject* context)
    : _application(gum::make_shared_ref<igd::app::Application>())
    , _worker(gum::make_shared_ref<MainLoopQueue>(context)) {}
}
