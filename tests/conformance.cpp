#include <gpio/port.hpp>
#include <gpio/output_setup.hpp>
#include <gpio/output_latch.hpp>
#include <gpio/output_toggle.hpp>
#include <gpio/pull_control.hpp>

#include <cassert>

using namespace mhaa::gpio;

class Fake final : public OutputSetup
{
public:
    bool valid(PinId pin) const override { return pin == static_cast<PinId>(2); }
    Status set_direction(PinId pin, Direction direction) override
    {
        if (!valid(pin))
        {
            return Status::InvalidPin;
        }
        output = direction == Direction::Output;
        return Status::Success;
    }

    Status write(PinId pin, Level level) override
    {
        if (!valid(pin))
        {
            return Status::InvalidPin;
        }
        if (!output)
        {
            return Status::WrongDirection;
        }
        latch = level;
        return Status::Success;
    }

    Status read(PinId pin, Level &level) const override
    {
        if (!valid(pin))
        {
            return Status::InvalidPin;
        }
        level = physical;
        return Status::Success;
    }

    Status configure_output(PinId pin, Level initial) override
    {
        if (!valid(pin))
        {
            return Status::InvalidPin;
        }
        latch = initial;
        output = true;
        ++setups;
        return Status::Success;
    }

    bool output = false;
    Level latch = Level::Low;
    Level physical = Level::Low;
    unsigned setups = 0;
};

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

class LatchedPort final : public Port, public OutputLatch, public OutputToggle
{
public:
    bool valid(PinId pin) const override { return pin == static_cast<PinId>(2); }
    Status set_direction(PinId pin, Direction value) override
    {
        if (!valid(pin))
        {
            return Status::InvalidPin;
        }
        direction = value;
        return Status::Success;
    }
    Status read(PinId pin, Level &level) const override
    {
        if (!valid(pin))
        {
            return Status::InvalidPin;
        }
        level = Level::Low;
        return Status::Success;
    }
    Status write(PinId pin, Level level) override
    {
        if (!valid(pin))
        {
            return Status::InvalidPin;
        }
        if (direction != Direction::Output)
        {
            return Status::WrongDirection;
        }
        latch = level;
        return Status::Success;
    }
    Status read_latch(PinId pin, Level &level) const override
    {
        if (!valid(pin))
        {
            return Status::InvalidPin;
        }
        level = latch;
        return Status::Success;
    }
    Status toggle(PinId pin) override
    {
        return write(pin, latch == Level::Low ? Level::High : Level::Low);
    }

private:
    Direction direction = Direction::Input;
    Level latch = Level::Low;
};

int main()
{
    Fake fake;
    OutputSetup &port = fake;
    assert(port.configure_output(static_cast<PinId>(2), Level::High) == Status::Success);
    Level level = Level::High;
    assert(port.read(static_cast<PinId>(2), level) == Status::Success && level == Level::Low);
    assert(port.read(static_cast<PinId>(3), level) == Status::InvalidPin && level == Level::Low);
    OptionalControls controls;
    PullControl &pulls = controls;
    assert(pulls.set_pull(static_cast<PinId>(4), Pull::Up) == Status::InvalidPin);
    assert(pulls.set_pull(static_cast<PinId>(2), Pull::Down) == Status::Unsupported);
    assert(pulls.set_pull(static_cast<PinId>(2), Pull::Up) == Status::Success);
    LatchedPort latched;
    OutputLatch &latch = latched;
    OutputToggle &toggle = latched;
    assert(toggle.toggle(static_cast<PinId>(2)) == Status::WrongDirection);
    assert(latched.set_direction(static_cast<PinId>(2), Direction::Output) == Status::Success);
    assert(toggle.toggle(static_cast<PinId>(2)) == Status::Success);
    assert(latch.read_latch(static_cast<PinId>(2), level) == Status::Success && level == Level::High);
}
