#include <ui/backend/Environment.hxx>

#include <QQmlContext>

#include <functional>

namespace ui {

GUM_DEFINE_LOGGER(Environment);

using namespace std::placeholders;

Environment::Environment(QObject*) {
    GUM_THROW(gum::NotImplementedException());
}

Environment::Environment(const QQmlEngine& qmlEngine, const UiContextRef& uiContext)
    : _uiContext(uiContext)
    , _surfaceModel(new SurfaceModel(this)) {
    qmlEngine.rootContext()->setContextProperty("global_backend_environment", this);

    const auto environment = _uiContext->getApplication().getEnvironment();
    _currentLocationChangedConnection = environment->currentLocationChanged().connect(std::bind(&Self::OnCurrentLocation, this, _1), _uiContext->getWorker());
}

void Environment::OnCurrentLocation(const igd::IReadonlyLocationPtr& currentLocation) {
    _currentLocationConnections.reset();

    _surfaceModel->removeRows(0, _surfaceModel->rowCount());
    if (!currentLocation)
        return;

    currentLocation->getReadonlySurfaceSize()->changed().connect(std::bind(&Self::OnCurrentSurfaceSizeChanged, this, _1), _uiContext->getWorker(),
                                                                 _currentLocationConnections);
    currentLocation->getReadonlySurfaceMap()->changed().connect(std::bind(&Self::OnCurrentSurfaceMapChanged, this, _1, _2, _3), _uiContext->getWorker(),
                                                                _currentLocationConnections);
}

void Environment::OnCurrentSurfaceSizeChanged(const igd::SurfaceSize& surfaceSize) {
    _logger.info() << "OnCurrentSurfaceSizeChanged([" << surfaceSize.x() << ", " << surfaceSize.y() << "])";

    _surfaceModel->resize(surfaceSize);
}

void Environment::OnCurrentSurfaceMapChanged(gum::MapOp op, const igd::SurfaceDescriptor& surfaceDescriptor, const igd::ISurfaceUnitRef& surfaceUnit) {
    switch (op) {
    case gum::MapOp::Added:
    case gum::MapOp::Updated:
        _surfaceModel->set(surfaceDescriptor, surfaceUnit);
        break;
    case gum::MapOp::Removed:
        _surfaceModel->erase(surfaceDescriptor);
        break;
    }
}
}
