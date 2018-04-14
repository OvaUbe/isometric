#pragma once

#include <igd/environment/surface/ISurfaceSize.hxx>
#include <igd/environment/surface/ISurfaceUnit.hxx>
#include <igd/environment/surface/SurfaceDescriptor.hxx>

#include <gum/Optional.h>

#include <QAbstractTableModel>

namespace ui {

class SurfaceModel : public QAbstractTableModel {
    Q_OBJECT

    Q_PROPERTY(int tableRowCount READ tableRowCount NOTIFY tableRowCountChanged)
    Q_PROPERTY(int tableColumnCount READ tableColumnCount NOTIFY tableColumnCountChanged)

    GUM_ENUM(CustomRoles, MaterialName = Qt::UserRole + 1, Level);

    using Cell = igd::ISurfaceUnitPtr;
    using Table = std::vector<Cell>;

  private:
    size_t _rowCount;
    size_t _columnCount;

    Table _table;

    QHash<int, QByteArray> _roleNames;

  public:
    SurfaceModel(QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;

    QHash<int, QByteArray> roleNames() const override {
        return _roleNames;
    }

    Q_INVOKABLE int tableRowCount() const {
        return _rowCount;
    }

    Q_INVOKABLE int tableColumnCount() const {
        return _columnCount;
    }

    void resize(const igd::SurfaceSize& surfaceSize);
    void set(const igd::SurfaceDescriptor& surfaceDescriptor, const igd::ISurfaceUnitRef& surfaceUnit);
    void erase(const igd::SurfaceDescriptor& surfaceDescriptor);

  signals:
    void tableRowCountChanged();
    void tableColumnCountChanged();

  private:
    size_t tableIndexFromIndex(const QModelIndex& index) const;

    QModelIndex indexFromSurfaceDescriptor(const igd::SurfaceDescriptor& surfaceDescriptor) const;
};
}
