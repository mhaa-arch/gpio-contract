#ifndef MHAA_GPIO_PORT_HPP
#define MHAA_GPIO_PORT_HPP

#include <gpio/types.hpp>

namespace mhaa
{
    namespace gpio
    {
        /** @brief A single logical digital port with zero-based pin identifiers. */
        class Port
        {
        public:
            virtual ~Port() = default;
            virtual bool valid(PinId pin) const = 0;
            virtual Status set_direction(PinId pin, Direction direction) = 0;

            /** @brief Writes the drive level of a configured output. */
            virtual Status write(PinId pin, Level level) = 0;

            /** @brief Samples the physical input. Leaves level unchanged on failure. */
            virtual Status read(PinId pin, Level &level) const = 0;
        };
    }
}

#endif
