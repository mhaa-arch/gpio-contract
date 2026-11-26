#ifndef MHAA_GPIO_TYPES_HPP
#define MHAA_GPIO_TYPES_HPP

#include <stdint.h>

namespace mhaa
{
    namespace gpio
    {
        enum class PinId : uint16_t
        {
        };

        enum class Direction
        {
            Input,
            Output
        };

        enum class Level
        {
            Low,
            High
        };

        enum class Pull
        {
            None,
            Up,
            Down
        };

        enum class Status
        {
            Success,
            InvalidPin,
            Unsupported,
            WrongDirection,
            Error
        };
    }
}

#endif
