#ifndef MHAA_GPIO_OUTPUT_LATCH_HPP
#define MHAA_GPIO_OUTPUT_LATCH_HPP

#include <gpio/types.hpp>

namespace mhaa
{
    namespace gpio
    {
        /** @brief Reads the programmed output value independently of the physical input. */
        class OutputLatch
        {
        public:
            virtual ~OutputLatch() = default;
            virtual Status read_latch(PinId pin, Level &level) const = 0;
        };
    }
}

#endif
