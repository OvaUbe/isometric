#pragma once

#include <QQmlEngine>

#include <ui/backend/UiContext.hxx>

namespace ui {

class Launcher : public QObject {
    using Self = Launcher;

    Q_OBJECT
    Q_PROPERTY(bool isGameActive READ isGameActive NOTIFY gameStatusChanged)

  private:
    UiContextPtr _uiContext;

    bool _isGameActive;

    gum::Token _startGameToken;
    gum::Token _launcherConnection;

  public:
    Launcher(QObject* parent = nullptr);
    Launcher(const QQmlEngine& qmlEngine, const UiContextRef& uiContext);

    Q_INVOKABLE bool isGameActive() const {
        return _isGameActive;
    }

    Q_INVOKABLE void newGame();
    Q_INVOKABLE void quitGame();

  signals:
    void gameStatusChanged();

  private:
    void OnGameStatusChanged(bool status);
};
}
