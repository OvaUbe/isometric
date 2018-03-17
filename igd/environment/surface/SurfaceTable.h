#pragma once

#include <igd/environment/surface/ISurfaceMap.h>

#include <vector>

namespace igd {

class SurfaceTable : public virtual ISurfaceMap {
    using Table = std::vector<ISurfaceUnitPtr>;

private:
    const size_t                        _width;
    size_t                              _count;

    Table                               _table;
    gum::Signal<ChangedSignature>       _tableChanged;

public:
    SurfaceTable(size_t width, size_t height);

    void set(const SurfaceDescriptor& surfaceDescriptor, const ISurfaceUnitRef& surfaceUnit) override;
    bool remove(const SurfaceDescriptor& surfaceDescriptor) override;
    void clear() override;

    gum::Optional<ISurfaceUnitRef> get(const SurfaceDescriptor& surfaceDescriptor) const override;
    bool contains(const SurfaceDescriptor& surfaceDescriptor) const override;

    bool is_empty() const override {
        return get_count();
    }

    size_t get_count() const override {
        gum::SignalLock l(_tableChanged.get_mutex());
        return _count;
    }

    const gum::SignalMutex& get_mutex() const override {
        return _tableChanged.get_mutex();
    }

    gum::SignalHandle<ChangedSignature> changed() const override {
        return _tableChanged.get_handle();
    }

private:
    void tableChangedPopulator(const std::function<ChangedSignature>& slot) const;

    ISurfaceUnitPtr doGet(const SurfaceDescriptor& surfaceDescriptor) const;

    SurfaceDescriptor makeDescriptor(size_t index) const;
    size_t indexOf(const SurfaceDescriptor& surfaceDescriptor) const;
};

}
