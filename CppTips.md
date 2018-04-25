## Use const everywhere

The _absence_ of `const` tells the reader of some special semantics.

## Follow RAII principles

- Avoid manual memory management
- Avoid manual mutex locking/unlocking
- Avoid hand-rolled destructors, use `gum::Token` instead
- You name it

```c++
// Bad:
Foo::Foo(const IFileDescriptorRef& fd)
    :   _fd(fd) { }

Foo::~Foo() { _fd->unlink(); }
/*
 * Actually a bug here, possible std::terminate in case unlink() throws
 * Needs to be wrapped in try { ... }
 */

// Good:
Foo::Foo(const IFileDescriptorRef& fd)
    :   _fd(fd),
        _deleter(make_token<FunctionToken>([=]{ fd->unlink(); })) { }
/* Automatically wrapped in try { ... } */
```

## Do not save on identifiers

Don't be afraid of lengthy identifiers - cropping names makes code look ugly and less readable. It also increases the possibility of symbol collision.

```c++
class AppCtx { ... }; // Bad

class ApplcationContext { ... }; // Good
```

>>>
**Note:** Follow this rule sparingly. There are some classic cases for cropped identifiers, e.g. `iter` (iterator), `fd` (file descriptor) and etc. Those are well-understood for historical reasons.
>>>

## Prefer `gum::range` to C-style counter loops

`gum::range` allows writing python-like counter loops using C++ `range-based for`. See `gum/Range.h`.

```c++
// Acceptable:
for (auto i = Start; i < Count; ++i) { ... }

// Better:
for (auto i : range(Start, Count)) { ... }
```

## Avoid output-only parameters

Use `gum::Optional`, `std::tuple`, `std::pair`.
See

- https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f20-for-out-output-values-prefer-return-values-to-output-parameters
- https://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#f21-to-return-multiple-out-values-prefer-returning-a-tuple-or-struct.

## Prefer references to raw pointers

References enforce type-safety, use references instead of raw pointers where possible.

```c++
// Bad:
class Wrapper {
    Value* _wrapped;
...
};

// Acceptable:
class Wrapper {
    Value& _wrapped;
...
};
```

In case it's necessary to use raw pointer in interface, use `gum::Optional<T&>`. This is a template specialization, which is a wrapper around raw pointer, but the difference is:
- Exceptions instead of segfaults on nullptr
- Makes clear the intentions of the interface - "Attention - this can be null".

```c++
virtual JpegRef IImageManager::makeJpeg(ByteArray data, const Meta* meta) = 0;
// I wonder if the meta can be null...

virtual JpegRef IImageManager::makeJpeg(ByteArray data, Optional<const Meta&> meta) = 0;
// Self-explanatory
```

## Prefer `gum` smartpointers to Qt/boost/std ones

`gum` smartpointers throw `NullPointerException` with backtrace instead of segfaulting.

## Prefer `gum::SharedReference` to `gum::SharedPtr`

`gum::SharedReference` is a non-null version of `gum::SharedPtr`, which makes it more effective - no more checks on every dereferencing operation. Also, makes interface more clear - no null possibility.

## Do not `catch (...)`

There is no reason for this. Anything which is not an instance of `std::exception` is a bug or runtime-specific magic and _is meant to_ unwind the whole stack.

Also dangerous in POSIX environment - see https://udrepper.livejournal.com/21541.html.

## Do not build logic on exception type

This is a very fragile design, since any polymorphic layer can throw anything, and this will not be so tomorrow.

Prefer returning errors for special logic.

```c++
// Bad:
try {
    _pipe->Write(...);
} catch (const PipeClosedException& ex) {
    // Special magic here
} catch (const std::exception& ex) {
    // Generic error handling
}

// Good:
try {
    const PipeError error = _pipe->Write(...);
    switch (error) { ... }
} catch (const std::exception& ex) {
    // Generic error handling
}
```

## Use `auto` sparingly

`auto` serves two purposes:
- Allow compiler to infer type in generic code, which would be impossible using other instruments;
- Improve code readability

There is no rule of thumb for `auto`, but I personally tend to avoid it. Explicit typing usually improves readability. However, `auto` can decrease code duplication. Here are some examples:

```c++
template < typename From_, typename To_, typename Fraction_ >
/* What is the return type? auto is functionally essential here */
lerp(From_ from, To_ to, Fraction_ fraction) {
    return from + (to - from) * fraction;
}
```

```c++
// What is info?
const auto info = material->GetExtendedInfo();

// A-ha!
const Optional<String> info = material->GetExtendedInfo();
```

```c++
// No reason for type duplication:
const LowMemoryTrait lowMemoryTrait = PlatformInformation::get().getTrait<LowMemoryTrait>();

// Better:
const auto lowMemoryTrait = PlatformInformation::get().getTrait<LowMemoryTrait>();
```

## Avoid nested lambdas

The ability to write nested lambdas does not make you FP guru.
```c++
// Bad:
void SceneManager::createScene() {
    ...
    return make_token<FunctionToken>([this]{
        _worker->push([this] {
            _logger.info() << "deleteScene()";
            _timeoutConnection = _worker->setTimer(5s, [this]{
                _logger.info() << "deferredSceneDeinitialization()";
                ...
                _environmentConnection = _environment->onCreated([this]{
                    _logger.info() << "onEnvironmentRecreated()";
                    ...
                }, _worker);
            });
        );
    });
}

// Good:
void SceneManager::createScene() {
    ...
    return make_token<FunctionToken>([this]{ _worker->push([this]{ deleteScene(); }); });
    /* One nested lambda is already confusing, but this simple case is acceptable */
}

void SceneManager::deleteScene() {
    _logger.info() << "deleteScene()";
    ...
    _timeoutConnection = _worker->setTimer(5s, [this]{ deferredSceneDeinitialization(); });
}

void SceneManager::deferredSceneDeinitialization() {
    _logger.info() << "deferredSceneDeinitialization()";
    ...
    _environmentConnection = _environment->onRecreated([this]{ onEnvironmentRecreated(); }, _worker);
}

void SceneManager::onEnvironmentRecreated() {
    _logger.info() << "onEnvironmentRecreated()";
    ...
}
```

## Never pass raw pointers to foreign code without life assurance

It's often necessary to pass `this` to signal handlers or worker tasks. Never do this without additional protection.

Available solutions:
- `gum::LifeToken`
- pimpl idiom

E.g:

```c++
// Bad:
_worker->push([this]{ asyncExecution(); });

// Good:
_worker->push([=]{ _impl->asyncExecution(); });
/* _impl is a shared smartpointer here */

// Good:
_worker->push(gum::make_cancellable([this]{ asyncExecution(); }, _lifeToken.get_handle()));
```

## Prefer polymorphic containers in interfaces

```c++
// Bad:
virtual void processImages(const SharedReference<std::map<Path, IFileDescriptorRef>>& imageFiles) = 0;

// Good:
using ImageFiles = IMap<Path, IFileDescriptorRef>;
GUM_DECLARE_REF(ImageFiles);
...
virtual void processImages(const ImageFilesRef& imageFiles) = 0;
```
