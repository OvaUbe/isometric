#include <igd/environment/surface/SurfaceTable.hxx>

#include <gum/Range.h>

namespace igd {

SurfaceTable::SurfaceTable(size_t width, size_t height)
    :   _width(width),
        _count(),
        _table(width * height),
        _tableChanged([this](const auto& slot){ tableChangedPopulator(slot); }) {
    GUM_CHECK(width, gum::ArgumentException("width", width));
    GUM_CHECK(height, gum::ArgumentException("height", height));
}


void SurfaceTable::set(const SurfaceDescriptor& surfaceDescriptor, const ISurfaceUnitRef& surfaceUnit) {
    gum::SignalLock l(_tableChanged.get_mutex());

    const auto index = indexOf(surfaceDescriptor);
    GUM_CHECK_INDEX(index, _table.size());

    const auto update = (bool)_table[index];
    _table[index] = surfaceUnit;

    const gum::MapOp op = update ? gum::MapOp::Updated : (++_count, gum::MapOp::Added);
    _tableChanged(op, surfaceDescriptor, surfaceUnit);
}


bool SurfaceTable::remove(const SurfaceDescriptor& surfaceDescriptor) {
    gum::SignalLock l(_tableChanged.get_mutex());

    const auto index = indexOf(surfaceDescriptor);
    if (index >= _table.size())
        return false;

    const auto surfaceUnit = _table[index];
    if (!surfaceUnit)
        return false;

    _table[index] = nullptr;
    --_count;
    _tableChanged(gum::MapOp::Removed, surfaceDescriptor, surfaceUnit);

    return true;
}


void SurfaceTable::clear() {
    gum::SignalLock l(_tableChanged.get_mutex());

    for (const auto i : gum::range<size_t>(0, _table.size())) {
        if (const auto surfaceUnit = _table[i]) {
            _table[i] = nullptr;
            _tableChanged(gum::MapOp::Removed, makeDescriptor(i), surfaceUnit);
        }
    }

    _count = 0;
}


gum::Optional<ISurfaceUnitRef> SurfaceTable::get(const SurfaceDescriptor& surfaceDescriptor) const {
    if (const auto surfaceUnit = doGet(surfaceDescriptor))
        return ISurfaceUnitRef(surfaceUnit);
    return nullptr;
}


bool SurfaceTable::contains(const SurfaceDescriptor& surfaceDescriptor) const {
    return (bool)doGet(surfaceDescriptor);
}


void SurfaceTable::tableChangedPopulator(const std::function<ChangedSignature>& slot) const {
    for (const auto i : gum::range<size_t>(0, _table.size()))
        if (const auto& surfaceUnit = _table[i])
            slot(gum::MapOp::Added, makeDescriptor(i), surfaceUnit);
}


ISurfaceUnitPtr SurfaceTable::doGet(const SurfaceDescriptor& surfaceDescriptor) const {
    gum::SignalLock l(_tableChanged.get_mutex());

    const auto index = indexOf(surfaceDescriptor);
    GUM_CHECK_INDEX(index, _table.size());

    return _table[index];
}


SurfaceDescriptor SurfaceTable::makeDescriptor(size_t index) const {
    return SurfaceDescriptor(index % _width, index / _width);
}


size_t SurfaceTable::indexOf(const SurfaceDescriptor& surfaceDescriptor) const {
    return _width * surfaceDescriptor.y + surfaceDescriptor.x;
}

}
