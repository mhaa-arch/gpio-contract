#include <gpio/port.hpp>

using namespace mhaa::gpio;

class Incomplete final : public Port
{
public:
    Status set_direction(PinId pin, Direction direction) override;
    Status write(PinId pin, Level level) override;
    Status read(PinId pin, Level &level) const override;
};

int main()
{
    Incomplete implementation;
    (void)implementation;
}
