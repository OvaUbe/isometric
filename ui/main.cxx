#include <ui/backend/Environment.hxx>
#include <ui/backend/Launcher.hxx>
#include <ui/backend/TypeRegistrator.hxx>
#include <ui/core/ToString.hxx>

#include <QCommandLineParser>
#include <QQmlEngine>
#include <QQuickView>
#include <QtGui/QGuiApplication>

#include <gum/concurrency/Thread.h>
#include <gum/log/LoggerManager.h>
#include <gum/log/sinks/AnsiTerminalLoggerSink.h>

using namespace ui;

namespace {

QString getCommandLineOption(const QCommandLineParser& parser, const QCommandLineOption& option) {
    const QString value = parser.value(option);
    GUM_CHECK(!value.isEmpty(), gum::String() << option.names() << " option was not specified");
    return value;
}
}

int do_main(int argc, char** argv) {
    QGuiApplication app(argc, argv);

    QCommandLineParser parser;
    parser.setApplicationDescription("Isometric");
    parser.addHelpOption();

    QCommandLineOption styleOption(
        QStringList() << "s"
                      << "style",
        "Custom ui style directory.",
        "style",
        "debug");
    parser.addOption(styleOption);

    parser.process(app);

    QQuickView mainView;
    QQmlEngine& qmlEngine = *mainView.engine();
    QObject::connect(&qmlEngine, &QQmlEngine::quit, &app, &QGuiApplication::quit);

    TypeRegistrator typeRegistrator(getCommandLineOption(parser, styleOption));

    const UiContextRef uiContext = gum::make_shared_ref<UiContext>(&app);
    Launcher launcher(qmlEngine, uiContext);
    Environment environment(qmlEngine, uiContext);

    mainView.setSource(QUrl::fromLocalFile(":/qml/Main.qml"));
    mainView.show();

    return app.exec();
}

int main(int argc, char** argv) {
    gum::Thread::set_own_name("ui");

    gum::Logger mainLogger("MainLogger");

    gum::Token terminalLoggerConnection = gum::LoggerManager::get().register_logger_sink(gum::make_shared_ref<gum::AnsiTerminalLoggerSink>());

    GUM_TRY_LOGGER("Terminated due to exception", gum::LogLevel::Error, mainLogger, return do_main(argc, argv));

    return 1;
}
