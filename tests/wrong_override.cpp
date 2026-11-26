#include <gpio/port.hpp>

using namespace mhaa::gpio;

class WrongOverride final : public Port
{
public:
    bool valid(PinId pin) override;
};
