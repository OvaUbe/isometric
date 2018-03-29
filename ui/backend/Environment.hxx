#pragma once

#include <ui/backend/UiContext.hxx>
#include <ui/backend/models/SurfaceModel.hxx>

#include <gum/token/GuardedTokenPool.h>

#include <QQmlEngine>

namespace ui {

class Environment : public QObject {
    using Self = Environment;

    Q_OBJECT

    Q_PROPERTY(QAbstractItemModel* surfaceModel READ surfaceModel)

  private:
    static gum::Logger _logger;

    UiContextPtr _uiContext;

    SurfaceModel* _surfaceModel;

    gum::GuardedTokenPool _currentLocationConnections;
    gum::Token _currentLocationChangedConnection;

  public:
    Environment(QObject* parent = nullptr);
    Environment(const QQmlEngine& qmlEngine, const UiContextRef& uiContext);

    Q_INVOKABLE SurfaceModel* surfaceModel() {
        return _surfaceModel;
    }

  private:
    void OnCurrentLocation(const igd::IReadonlyLocationPtr& currentLocation);
    void OnCurrentSurfaceSizeChanged(const igd::SurfaceSize& surfaceSize);
    void OnCurrentSurfaceMapChanged(gum::MapOp op, const igd::SurfaceDescriptor& surfaceDescriptor, const igd::ISurfaceUnitRef& surfaceUnit);
};
}
