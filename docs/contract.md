# GPIO contract

## Port and pin scope

[Port](../include/gpio/port.hpp) represents one logical bank. Its scoped 16-bit `PinId` values are zero-based and may have gaps. `valid(pin)` tests availability. Operations on an invalid pin report `InvalidPin`. Implementations must validate before applying the operation.

## Signal and drive state

`set_direction` selects input or output. `write` drives a configured output and reports `WrongDirection` otherwise. `read` samples the physical input and preserves its output argument on failure. Report `Unsupported` if the active configuration prevents physical sampling. `Error` signals an implementation failure.

## Optional controls

- [OutputSetup](../include/gpio/output_setup.hpp) extends the same port and sequences the initial level with output configuration. Electrical transients depend on the hardware.
- [OutputLatch](../include/gpio/output_latch.hpp) reads the programmed output level. A failed read preserves the supplied value.
- [OutputToggle](../include/gpio/output_toggle.hpp) toggles the programmed output on a supporting resource. Do not infer atomicity beyond the Adapter's guarantee.
- [PullControl](../include/gpio/pull_control.hpp) selects no bias, pull-up or pull-down as supported per pin.

## Implementation boundary

The Adapter owns resource state. The caller must keep the implementation alive during each call and arrange access from other execution contexts. Document the contexts and concurrency guarantees of the actual implementation. Shared public types are in [`gpio/types.hpp`](../include/gpio/types.hpp).
