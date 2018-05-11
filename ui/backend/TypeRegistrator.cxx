#include <ui/backend/TypeRegistrator.hxx>

#include <ui/backend/Environment.hxx>
#include <ui/backend/Launcher.hxx>
#include <ui/qml/runtime/Parallelogram.hxx>
#include <ui/qml/runtime/Triangle.hxx>

#include <QQmlEngine>

#include <gum/string/StringLiteral.h>

namespace ui {

namespace {

using UrlRegistratorSignture = int (*)(const QUrl&, const char*, int, int, const char*);
using TypeRegistratorSignture = int (*)(const char*, int, int, const char*);

template <typename Registrator_>
int doRegisterType(const Registrator_& registrator, const gum::StringLiteral& source, const gum::StringLiteral& typeName, const gum::StringLiteral& qualified) {
    return registrator(QUrl(source.c_str()), qualified.c_str(), 1, 0, typeName.c_str());
}

template <typename Registrator_>
int doRegisterType(const Registrator_& registrator, const gum::StringLiteral& typeName, const gum::StringLiteral& qualified) {
    return registrator(qualified.c_str(), 1, 0, typeName.c_str());
}

int registerType(const gum::StringLiteral& source, const gum::StringLiteral& typeName, const gum::StringLiteral& qualified) {
    return doRegisterType(static_cast<UrlRegistratorSignture>(&qmlRegisterType), source, typeName, qualified);
}

int registerType(const gum::StringLiteral& source, const gum::StringLiteral& typeName) {
    return registerType(source, typeName, typeName);
}

int registerSingleton(const gum::StringLiteral& source, const gum::StringLiteral& typeName, const gum::StringLiteral& qualified) {
    return doRegisterType(static_cast<UrlRegistratorSignture>(&qmlRegisterSingletonType), source, typeName, qualified);
}

int registerSingleton(const gum::StringLiteral& source, const gum::StringLiteral& typeName) {
    return registerSingleton(source, typeName, typeName);
}

template <typename Type_>
int registerType(const gum::StringLiteral& typeName, const gum::StringLiteral& qualified) {
    return doRegisterType(static_cast<TypeRegistratorSignture>(&qmlRegisterType<Type_>), typeName, qualified);
}

template <typename Type_>
int registerType(const gum::StringLiteral& typeName) {
    return registerType<Type_>(typeName, typeName);
}

template <typename Type_>
int registerSingleton(const gum::StringLiteral& typeName, const gum::StringLiteral& qualified) {
    return doRegisterType(static_cast<TypeRegistratorSignture>(&qmlRegisterSingletonType<Type_>), typeName, qualified);
}

template <typename Type_>
int registerSingleton(const gum::StringLiteral& typeName) {
    return registerSingleton<Type_>(typeName, typeName);
}

#define UI_DETAIL_DO_REGISTER_STYLE(Registrator_, Type_, Ns_, ChosenNs_)                                                                                       \
    do {                                                                                                                                                       \
        Registrator_("qrc:/qml/styles/" Ns_ "/" Type_ ".qml", Type_, "styles." Ns_ "." Type_);                                                                 \
        if (Ns_ == ChosenNs_)                                                                                                                                  \
            Registrator_("qrc:/qml/styles/" Ns_ "/" Type_ ".qml", Type_, "styles." Type_);                                                                     \
    } while (0)

#define UI_DETAIL_REGISTER_STYLE(Type_, Ns_, ChosenNs_) UI_DETAIL_DO_REGISTER_STYLE(registerType, Type_, Ns_, ChosenNs_)

#define UI_DETAIL_REGISTER_SINGLETON_STYLE(Type_, Ns_, ChosenNs_) UI_DETAIL_DO_REGISTER_STYLE(registerSingleton, Type_, Ns_, ChosenNs_)
}

TypeRegistrator::TypeRegistrator(const QString& chosenStyle) {
#define UI_DETAIL_REGISTER_STYLE_SOURCES(Ns_)                                                                                                                  \
    UI_DETAIL_REGISTER_SINGLETON_STYLE("LocationStyle", Ns_, chosenStyle);                                                                                     \
    UI_DETAIL_REGISTER_STYLE("SurfaceTile", Ns_, chosenStyle);                                                                                                 \
    UI_DETAIL_REGISTER_STYLE("Wall", Ns_, chosenStyle)

    UI_DETAIL_REGISTER_STYLE_SOURCES("debug");
    UI_DETAIL_REGISTER_STYLE_SOURCES("igd");

#undef UI_DETAIL_REGISTER_STYLE_SOURCES

    registerSingleton("qrc:/qml/Backend.qml", "Backend");

    registerType<Launcher>("Launcher", "backend.Launcher");
    registerType<Environment>("Environment", "backend.Environment");

    registerType<Parallelogram>("Parallelogram", "runtime.components.Parallelogram");
    registerType<Triangle>("Triangle", "runtime.components.Triangle");
}

#undef UI_DETAIL_DO_REGISTER_STYLE
#undef UI_DETAIL_REGISTER_STYLE
#undef UI_DETAIL_REGISTER_SINGLETON_STYLE
}
