#ifndef MHAA_GPIO_OUTPUT_TOGGLE_HPP
#define MHAA_GPIO_OUTPUT_TOGGLE_HPP

#include <gpio/types.hpp>

namespace mhaa
{
    namespace gpio
    {
        /** @brief Toggles the programmed output using a target-supported operation. */
        class OutputToggle
        {
        public:
            virtual ~OutputToggle() = default;
            virtual Status toggle(PinId pin) = 0;
        };
    }
}

#endif
