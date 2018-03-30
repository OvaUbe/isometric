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
}

TypeRegistrator::TypeRegistrator() {
    registerSingleton("qrc:/qml/Backend.qml", "Backend");

    registerSingleton("qrc:/qml/styles/debug/LocationStyle.qml", "LocationStyle", "styles.debug.LocationStyle");
    registerType("qrc:/qml/styles/debug/SurfaceTile.qml", "SurfaceTile", "styles.debug.SurfaceTile");

    registerSingleton("qrc:/qml/styles/debug/LocationStyle.qml", "LocationStyle", "styles.LocationStyle");
    registerType("qrc:/qml/styles/debug/SurfaceTile.qml", "SurfaceTile", "styles.SurfaceTile");

    registerType<ui::Launcher>("Launcher", "backend.Launcher");
    registerType<ui::Environment>("Environment", "backend.Environment");
}
}
