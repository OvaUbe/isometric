#include <ui/backend/Launcher.h>
#include <ui/backend/TypeRegistrator.h>

#include <QtGui/QGuiApplication>
#include <QQmlEngine>
#include <QQuickView>

using namespace ui;


int main(int argc, char** argv) {
    QGuiApplication app(argc, argv);

    QQuickView mainView(QUrl::fromLocalFile(":/qml/Main.qml"));
    QQmlEngine& qmlEngine = *mainView.engine();
    QObject::connect(&qmlEngine, &QQmlEngine::quit, &app, &QGuiApplication::quit);

    TypeRegistrator typeRegistrator;

    const UiContextRef uiContext = gum::make_shared_ref<UiContext>();
    Launcher launcher(qmlEngine, uiContext);

    mainView.show();

    return app.exec();
}
