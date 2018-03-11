#pragma once

#include <QObject>
#include <QString>

namespace ui {

class Launcher : public QObject {
    Q_OBJECT

public:
    explicit Launcher(QObject *parent = nullptr);

    Q_INVOKABLE void newGame();
};

}
