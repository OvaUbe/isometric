#pragma once

#include <igd/environment/location/ILocation.hxx>

#include <gum/async/ITaskQueue.h>
#include <gum/io/async/IAsyncByteStream.h>

namespace igd {

class TiledMapParser {
    class Impl;
    GUM_DECLARE_UNIQUE_REF(Impl);

  public:
    using LocationOrError = gum::ErrorOr<ILocationRef>;

    using LocationReadySignature = void(const LocationOrError&);

  private:
    ImplUniqueRef _impl;

  public:
    TiledMapParser(const gum::ITaskQueueRef& worker, const gum::String& filePath);

    TiledMapParser(TiledMapParser&& other);
    TiledMapParser& operator=(TiledMapParser&& other);

    ~TiledMapParser();

    gum::SignalHandle<LocationReadySignature> locationReady() const;
};
}
