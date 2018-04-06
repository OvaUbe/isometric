#include <ui/backend/models/SurfaceModel.hxx>

#include <gum/maybe/Maybe.h>

namespace ui {

namespace {

struct MaterialVisitor : public boost::static_visitor<gum::String> {
    template <typename Material_>
    gum::String operator()(const Material_& material) const {
        return material.getName().to_string();
    }
};
}

SurfaceModel::SurfaceModel(QObject* parent)
    : QAbstractTableModel(parent)
    , _rowCount()
    , _columnCount() {
    _roleNames.insert(Qt::DisplayRole, "display");

    _roleNames.insert(CustomRoles::MaterialName, "materialName");
}

int SurfaceModel::rowCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : _table.size();
}

int SurfaceModel::columnCount(const QModelIndex& parent) const {
    return parent.isValid() ? 0 : 1;
}

QVariant SurfaceModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid())
        return QVariant();

    return gum::maybe(_table[tableIndexFromIndex(index)])
        .and_([&](const auto& material) {
            switch (role) {
            case Qt::DisplayRole:
                return QVariant(true);
            case CustomRoles::MaterialName:
                return QVariant(material.c_str());
            default:
                return QVariant();
            }
        })
        .or_bind(QVariant())
        .unwrap();
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

    _table[tableIndex] = boost::apply_visitor(MaterialVisitor(), surfaceUnit->getMaterial());
    emit dataChanged(index, index);
}

void SurfaceModel::erase(const igd::SurfaceDescriptor& surfaceDescriptor) {
    const QModelIndex index = indexFromSurfaceDescriptor(surfaceDescriptor);
    const size_t tableIndex = tableIndexFromIndex(index);

    _table[tableIndex] = nullptr;
    emit dataChanged(index, index);
}

size_t SurfaceModel::tableIndexFromIndex(const QModelIndex& index) const {
    GUM_CHECK_INDEX((size_t)index.row(), _table.size());
    return index.row();
}

QModelIndex SurfaceModel::indexFromSurfaceDescriptor(const igd::SurfaceDescriptor& surfaceDescriptor) const {
    return createIndex(_columnCount * surfaceDescriptor.y() + surfaceDescriptor.x(), 0);
}
}
