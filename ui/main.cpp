#include <ui/backend/TypeRegistrator.h>

#include <QtGui/QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);

    ui::TypeRegistrator typeRegistrator;

    QQuickView view(QUrl::fromLocalFile(":/qml/Main.qml"));
    QObject::connect(view.engine(), &QQmlEngine::quit, &app, &QGuiApplication::quit);

    view.show();

    return app.exec();
}
