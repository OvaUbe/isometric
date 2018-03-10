#include <QtGui/QGuiApplication>
#include <QtQuick/QQuickView>

int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);

    QQuickView view;
    view.setSource(QUrl::fromLocalFile(":/qml/MainMenu.qml"));
    view.show();

    return app.exec();
}
