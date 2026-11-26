#ifndef MHAA_GPIO_OUTPUT_SETUP_HPP
#define MHAA_GPIO_OUTPUT_SETUP_HPP

#include <gpio/port.hpp>
#include <gpio/types.hpp>

namespace mhaa
{
    namespace gpio
    {
        /** @brief Configures an output and its initial level with target-aware sequencing. */
        class OutputSetup : public Port
        {
        public:
            virtual Status configure_output(PinId pin, Level initial_level) = 0;
        };
    }
}

#endif
