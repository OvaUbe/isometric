#include <ui/backend/models/SurfaceModel.hxx>

#include <igd/core/Geometry.hxx>

#include <gum/maybe/Maybe.h>

#include <QPoint>

namespace ui {

namespace {

struct MaterialVisitor : public boost::static_visitor<QVariant> {
    template <typename Material_>
    QVariant operator()(const Material_& material) const {
        return material.getName().c_str();
    }
};
}

SurfaceModel::SurfaceModel(QObject* parent)
    : QAbstractTableModel(parent)
    , _rowCount()
    , _columnCount() {
    _roleNames.insert(Qt::DisplayRole, "display");
    _roleNames.insert(CustomRoles::MaterialName, "materialName");
    _roleNames.insert(CustomRoles::Level, "level");
    _roleNames.insert(CustomRoles::TilesetPath, "tilesetPath");
    _roleNames.insert(CustomRoles::TileId, "tileId");
    _roleNames.insert(CustomRoles::TileSide, "tileSide");
}

int SurfaceModel::rowCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : int(_table.size());
}

int SurfaceModel::columnCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : 1;
}

QVariant SurfaceModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    const auto surfaceUnit = _table[tableIndexFromIndex(index)];
    if (!surfaceUnit)
        return QVariant();

    switch (role) {
    case Qt::DisplayRole:
        return QVariant(true);
    case CustomRoles::MaterialName:
        return boost::apply_visitor(MaterialVisitor(), surfaceUnit->getMaterial());
    case CustomRoles::Level:
        if (const auto level = surfaceUnit->getLevel())
            return int(*level);
        return QVariant();
    case CustomRoles::TilesetPath:
        return surfaceUnit->getTileInfo().TilesetPath.c_str();
    case CustomRoles::TileId: {
        const igd::Position<2> tileId = surfaceUnit->getTileInfo().TileId;
        return QPoint(int(tileId.x()), int(tileId.y()));
    }
    case CustomRoles::TileSide:
        return surfaceUnit->getTileInfo().TileSide;
    default:
        return QVariant();
    }
}

void SurfaceModel::resize(const igd::SurfaceSize& surfaceSize) {
    emit beginResetModel();

    _table = Table();

    _rowCount = surfaceSize[1];
    _columnCount = surfaceSize[0];
    _table.resize(_rowCount * _columnCount);

    emit endResetModel();

    emit tableRowCountChanged();
    emit tableColumnCountChanged();
}

void SurfaceModel::set(const igd::SurfaceDescriptor& surfaceDescriptor, const igd::ISurfaceUnitRef& surfaceUnit) {
    const QModelIndex index = indexFromSurfaceDescriptor(surfaceDescriptor);
    const size_t tableIndex = tableIndexFromIndex(index);

    _table[tableIndex] = surfaceUnit;
    emit dataChanged(index, index);
}

void SurfaceModel::erase(const igd::SurfaceDescriptor& surfaceDescriptor) {
    const QModelIndex index = indexFromSurfaceDescriptor(surfaceDescriptor);
    const size_t tableIndex = tableIndexFromIndex(index);

    _table[tableIndex] = nullptr;
    emit dataChanged(index, index);
}

size_t SurfaceModel::tableIndexFromIndex(const QModelIndex& index) const {
    GUM_CHECK_INDEX(size_t(index.row()), _table.size());
    return size_t(index.row());
}

QModelIndex SurfaceModel::indexFromSurfaceDescriptor(const igd::SurfaceDescriptor& surfaceDescriptor) const {
    return createIndex(int(_columnCount * surfaceDescriptor.y() + surfaceDescriptor.x()), 0);
}
}
