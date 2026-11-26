# Porting the GPIO Contract

Hardware Definitions describe ports, pin routing and available bias or latch facilities. The Adapter maps those facts to the logical port and checks individual pins. A future Devices composition can map a board signal to a port plus its `PinId`. The same numeric ID can name unrelated pins on different ports.

Targets vary in whether physical input can be sampled in output mode, whether pulls can be disabled or selected individually and whether native toggle exists. Electrical output enable timing and cross-context atomicity require target-specific evidence.

This repository's host simulations and shared API compile/link checks provide source-level evidence. Target timing and physical behavior require hardware validation.
