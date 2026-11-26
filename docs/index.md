# GPIO Contract guide

A pin's physical input and its output latch can report different levels. Each `PinId` is scoped to its port. Start with pin identity and the difference between input and latch, then choose the capabilities the board needs.

1. Start with [the contract](contract.md) for implementer obligations and capability boundaries.
2. Read [the conformance example](examples.md) for an implementation you can compile locally.
3. Consult [the portability notes](compatibility.md) before choosing a hardware mapping.