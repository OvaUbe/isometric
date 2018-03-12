#pragma once

#include <QQmlEngine>

#include <ui/backend/UiContext.h>

namespace ui {

class Launcher : public QObject {
    Q_OBJECT

private:
    UiContextPtr _uiContext;

public:
    Launcher(QObject* parent = nullptr);
    Launcher(const QQmlEngine& qmlEngine, const UiContextRef& iuContext);

    Q_INVOKABLE void newGame();
};

}
