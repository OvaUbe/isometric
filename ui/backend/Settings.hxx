#pragma once

#include <ui/backend/UiContext.hxx>

#include <QQmlEngine>

namespace ui {

class Settings : public QObject {
    using Self = Settings;

    Q_OBJECT

    Q_PROPERTY(QString chosenApplicationStyle READ chosenApplicationStyle WRITE setChosenApplicationStyle NOTIFY chosenApplicationStyleChanged)

  private:
    QString _chosenApplicationStyle;

  public:
    Settings(QObject* = nullptr);
    Settings(const QQmlEngine& qmlEngine, const UiContextRef& uiContext);

    Q_INVOKABLE QString chosenApplicationStyle() const {
        return _chosenApplicationStyle;
    }

    Q_INVOKABLE void setChosenApplicationStyle(QString chosenApplicationStyle) {
        if (_chosenApplicationStyle == chosenApplicationStyle)
            return;

        _chosenApplicationStyle = chosenApplicationStyle;
        emit chosenApplicationStyleChanged();
    }

  signals:
    void chosenApplicationStyleChanged();
};
}
