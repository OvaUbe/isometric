#include <igd/environment/tiled/TiledMapParser.hxx>

#include <igd/core/Core.hxx>
#include <igd/core/ToString.hxx>
#include <igd/environment/location/Location.hxx>
#include <igd/environment/surface/SurfaceTable.hxx>
#include <igd/environment/surface/SurfaceUnit.hxx>

#include <gum/Range.h>
#include <gum/string/ToString.h>

#include <functional>

#include <TmxMap.h>
#include <TmxPropertySet.h>
#include <TmxTile.h>
#include <TmxTileLayer.h>
#include <TmxTileset.h>

namespace igd {

namespace {

GUM_DECLARE_EXCEPTION(TiledMapParserException, "Tiled map parsing failed");
}

using namespace std::placeholders;

using TmxPropertyMap = std::unordered_map<std::string, Tmx::Property>;

class TiledMapParser::Impl {
    using Self = Impl;

    using LocationOrError = TiledMapParser::LocationOrError;
    using LocationReadySignature = TiledMapParser::LocationReadySignature;

  private:
    static gum::Logger _logger;

    gum::Optional<LocationOrError> _location;
    gum::Signal<LocationReadySignature> _locationReady;

    gum::ITaskQueueRef _worker;

    gum::LifeToken _lifeToken;

  public:
    Impl(const gum::ITaskQueueRef& worker, const gum::String& filePath)
        : _locationReady([this](const auto& slot) {
            if (_location)
                slot(*_location);
        })
        , _worker(worker) {
        _worker->push(gum::make_cancellable(std::bind(&Self::parse, this, filePath), _lifeToken));
    }

    gum::SignalHandle<LocationReadySignature> locationReady() {
        return _locationReady.get_handle();
    }

  private:
    void parse(const gum::String& filePath) {
        try {
            doParse(filePath);
        } catch (const std::exception& ex) {
            setParseResult(gum::ExceptionRef(gum::make_shared_ref<TiledMapParserException>(gum::to_string(ex))));
        }
    }

    void doParse(const gum::String& filePath) {
        Tmx::Map map;
        map.ParseFile(std::string(filePath));
        GUM_CHECK(!map.HasError(), gum::String() << "Failed to parse tiled map. " << map.GetErrorText() << " (" << map.GetErrorCode() << ")");

        const SurfaceSize surfaceSize(map.GetWidth(), map.GetHeight());
        const ISurfaceMapRef surfaceMap = gum::make_shared_ref<SurfaceTable>(surfaceSize.x(), surfaceSize.y());

        for (auto layer : gum::range(0, map.GetNumTileLayers())) {
            const Tmx::TileLayer& tileLayer = *GUM_ASSERT(map.GetTileLayer(layer));

            for (auto width : gum::range(0, tileLayer.GetWidth())) {
                for (auto height : gum::range(0, tileLayer.GetHeight())) {
                    const Tmx::MapTile& mapTile = tileLayer.GetTile(width, height);
                    if (mapTile.tilesetId < 0)
                        continue;

                    const SurfaceDescriptor tilePosition(width, height);
                    const Tmx::Tileset& tileset = *GUM_ASSERT(map.GetTileset(mapTile.tilesetId));
                    const Tmx::Tile& tile = *GUM_ASSERT(tileset.GetTile(int(mapTile.id)));
                    const TmxPropertyMap& tileProperties = tile.GetProperties().GetPropertyMap();

                    SurfaceMaterial material = parseMaterial(tilePosition, tileProperties);
                    TileInfo tileInfo = makeTileInfo(tile, tileset);

                    surfaceMap->set(tilePosition, gum::make_shared_ref<SurfaceUnit>(std::move(material), std::move(tileInfo)));
                }
            }
        }

        setParseResult(ILocationRef(gum::make_shared_ref<Location>(surfaceSize, surfaceMap)));
    }

    SurfaceMaterial parseMaterial(const SurfaceDescriptor&, const TmxPropertyMap&) {
        return surface_materials::Stub();
    }

    TileInfo makeTileInfo(const Tmx::Tile& tile, const Tmx::Tileset& tileset) {
        GUM_CHECK(
            tileset.GetTileWidth() == tileset.GetTileHeight(),
            gum::String() << "Unable to work with uneven tile dimensions (" << tileset.GetTileWidth() << "x" << tileset.GetTileHeight() << " provided)");

        const Position<2> tileId(tile.GetId() % tileset.GetColumns(), tile.GetId() / tileset.GetColumns());
        const gum::String tilesetPath(tileset.GetImage()->GetSource());

        return TileInfo(tilesetPath, tileId, u32(tileset.GetTileWidth()));
    }

    void setParseResult(const LocationOrError& location) {
        gum::SignalLock l(_locationReady.get_mutex());

        if (_location)
            return;

        _location = location;
        _locationReady(*_location);
    }
};
GUM_DEFINE_NAMED_LOGGER(TiledMapParser::Impl, TiledMapParser);

TiledMapParser::TiledMapParser(const gum::ITaskQueueRef& worker, const gum::String& filePath)
    : _impl(gum::make_unique_ref<Impl>(worker, filePath)) {}

TiledMapParser::TiledMapParser(TiledMapParser&& other)
    : _impl(std::move(other._impl)) {}

TiledMapParser& TiledMapParser::operator=(TiledMapParser&& other) {
    _impl = std::move(other._impl);
    return *this;
}

TiledMapParser::~TiledMapParser() {}

gum::SignalHandle<TiledMapParser::LocationReadySignature> TiledMapParser::locationReady() const {
    return _impl->locationReady();
}
}
