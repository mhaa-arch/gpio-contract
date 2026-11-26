# GPIO Contract example

[The conformance program](../tests/conformance.cpp) pairs a simulated implementation with assertions at the Contract boundary. The bias fixture below implements only `PullControl`. It demonstrates separating an unavailable pin from an unsupported pull direction. The full program also configures an initial output level, verifies that the physical level can differ, and tests latch read and toggle through separate capabilities.

## Implementation excerpt

This class is taken from the program. The linked source contains the test cases and any additional fixtures.

```cpp
#include <gpio/port.hpp>
#include <gpio/output_setup.hpp>
#include <gpio/output_latch.hpp>
#include <gpio/output_toggle.hpp>
#include <gpio/pull_control.hpp>


using namespace mhaa::gpio;

class OptionalControls final : public PullControl
{
public:
    Status set_pull(PinId pin, Pull pull) override
    {
        if (pin != static_cast<PinId>(2))
        {
            return Status::InvalidPin;
        }
        return pull == Pull::Down ? Status::Unsupported : Status::Success;
    }
};
```

## Build and run

From this repository root, with assertions enabled, compile the full program. A passing run exits with status 0 and prints no output. Use `conformance.exe` on Windows.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude tests/conformance.cpp -o conformance
./conformance
```

To verify enforcement of the abstract interface, compile the two negative sources separately. The first should diagnose an abstract type and the second an incompatible override.

```sh
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/missing_override.cpp
g++ -std=c++11 -Wall -Wextra -Wpedantic -Werror -fno-rtti -fno-exceptions -Iinclude -fsyntax-only tests/wrong_override.cpp
```
