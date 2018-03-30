#include <ui/backend/TypeRegistrator.hxx>

#include <ui/backend/Environment.hxx>
#include <ui/backend/Launcher.hxx>

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

#define UI_DETAIL_DO_REGISTER_STYLE(Registrator_, Source_, Type_, Ns_, ChosenNs_)                                                                              \
    do {                                                                                                                                                       \
        Registrator_(Source_, Type_, "styles." Ns_ "." Type_);                                                                                                 \
        if (Ns_ == ChosenNs_)                                                                                                                                  \
            Registrator_(Source_, Type_, "styles." Type_);                                                                                                     \
    } while (0)

#define UI_DETAIL_REGISTER_STYLE(Source_, Type_, Ns_, ChosenNs_) UI_DETAIL_DO_REGISTER_STYLE(registerType, Source_, Type_, Ns_, ChosenNs_)

#define UI_DETAIL_REGISTER_SINGLETON_STYLE(Source_, Type_, Ns_, ChosenNs_) UI_DETAIL_DO_REGISTER_STYLE(registerSingleton, Source_, Type_, Ns_, ChosenNs_)
}

TypeRegistrator::TypeRegistrator() {
    const QString chosenStyle = "debug";

    registerSingleton("qrc:/qml/Backend.qml", "Backend");

    UI_DETAIL_REGISTER_SINGLETON_STYLE("qrc:/qml/styles/debug/LocationStyle.qml", "LocationStyle", "debug", chosenStyle);
    UI_DETAIL_REGISTER_STYLE("qrc:/qml/styles/debug/SurfaceTile.qml", "SurfaceTile", "debug", chosenStyle);

    registerType<ui::Launcher>("Launcher", "backend.Launcher");
    registerType<ui::Environment>("Environment", "backend.Environment");
}

#undef UI_DETAIL_DO_REGISTER_STYLE
#undef UI_DETAIL_REGISTER_STYLE
#undef UI_DETAIL_REGISTER_SINGLETON_STYLE
}
