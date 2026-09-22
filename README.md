# ema-filter

Exponential moving average, first sample taken without lag.

Part of [integra-lib](https://gitlab.integrasources.com/internal-projects/integra-lib).
Header-only C++20, no exceptions, no RTTI.

## Use it

```bash
git submodule add ../ema-filter.git external/integra/ema-filter
```

```cmake
add_subdirectory(external/integra/ema-filter)
target_link_libraries(app PRIVATE Integra::ema_filter)
```

```cpp
#include <integra/ema_filter.hpp>
```

## Develop it

```bash
cmake -S . -B build && cmake --build build -j && ctest --test-dir build
```

Tests are built only when this repository is the top-level project, so a consumer
never builds them. Style and pipeline come from the `ci-shared` submodule; run
`git submodule update --init` before `pre-commit`.
