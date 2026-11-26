#ifndef MHAA_GPIO_PULL_CONTROL_HPP
#define MHAA_GPIO_PULL_CONTROL_HPP

#include <gpio/types.hpp>

namespace mhaa
{
    namespace gpio
    {
        /** @brief Selects bias on pins of the represented port. */
        class PullControl
        {
        public:
            virtual ~PullControl() = default;
            virtual Status set_pull(PinId pin, Pull pull) = 0;
        };
    }
}

#endif
