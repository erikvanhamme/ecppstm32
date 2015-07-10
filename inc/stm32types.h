/*
 * Copyright 2015 Erik Van Hamme
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef STM32TYPES_H
#define STM32TYPES_H

#ifdef stm32f3
#include "stm32f3xx.h"
#endif

#ifdef stm32f4
#include "stm32f4xx.h"
#endif

#include <cstdint>

namespace ecpp {
    namespace stm32 {

        // TODO: find a generic templated way to deal with template prototypes and specialisations for masks

//        template<std::uint32_t... I>
//        struct mask_or;

//        template<>
//        struct mask_or<> {
//            static constexpr std::uint32_t value = 0;
//        };

//        template<std::uint32_t first, std::uint32_t... rest>
//        struct mask_or<first, rest...> {
//            static constexpr std::uint32_t value = first | mask_or<rest...>::value;
//        };

        enum class gpioport : std::uint32_t {
            pa = GPIOA_BASE,
            pb = GPIOB_BASE,
            pc = GPIOC_BASE,
            pd = GPIOD_BASE,
            pe = GPIOE_BASE,
            pf = GPIOF_BASE,
#ifdef stm32f4
            pg = GPIOG_BASE,
            ph = GPIOH_BASE,
            pi = GPIOI_BASE,
#endif
        };

        enum class gpiopin : std::uint32_t {
            p0 = (1 << 0),
            p1 = (1 << 1),
            p2 = (1 << 2),
            p3 = (1 << 3),
            p4 = (1 << 4),
            p5 = (1 << 5),
            p6 = (1 << 6),
            p7 = (1 << 7),
            p8 = (1 << 8),
            p9 = (1 << 9),
            p10 = (1 << 10),
            p11 = (1 << 11),
            p12 = (1 << 12),
            p13 = (1 << 13),
            p14 = (1 << 14),
            p15 = (1 << 15),
        };

        template<gpiopin... M>
        struct gpiopin_mask;

        template<>
        struct gpiopin_mask<> {
            static constexpr std::uint32_t value = 0;
        };

        template<gpiopin first, gpiopin... rest>
        struct gpiopin_mask<first, rest...> {
            static constexpr std::uint32_t value = static_cast<std::uint32_t>(first) | gpiopin_mask<rest...>::value;
        };

        enum class gpiomode {
            input_floating = 0, // Floating Input (MODE=00 TYPE=0 PUP=00)
            input_pullup = 1, // Pullup Input (MODE=00 TYPE=0 PUP=01)
            input_pulldown = 2, // Pulldown Input (MODE=00 TYPE=0 PUP=10)
            input_analog = 24, // Analog Input (MODE=11 TYPE=0 PUP=00)
            output_pushpull = 8, // Push Pull Output (MODE=01 TYPE=0 PUP=00)
            output_opendrain = 12, // Open Drain Output (MODE=01 TYPE=1 PUP=00)
            alternate = 16, // Alternate function (MODE=10 TYPE=0 PUP=00)
            alternate_opendrain = 20, // Alternate Open Drain (MODE=10 TYPE=1 PUP=00)
        };

        // TODO: Verify if this info is also valid for the other STM32 chips.
        enum class alternatefunction {
            rtc_50Hz = 0u, mco = 0u, tamper = 0u, swj = 0u, trace = 0u,
            tim1 = 1u, tim2 = 1u,
            tim3 = 2u, tim4 = 2u, tim5 = 2u,
            tim8 = 3u, tim9 = 3u, tim10 = 3u, tim11 = 3u,
            i2c1 = 4u, i2c2 = 4u, i2c3 = 4u,
            spi1 = 5u, spi2 = 5u, i2s2 = 5u, i2s2ext = 5u,
            spi3 = 6u, i2sext = 6u, i2s3 = 6u,
            usart1 = 7u, usart2 = 7u, usart3 = 7u, i2s3ext = 7u,
            uart4 = 8u, uart5 = 8u, usart6 = 8u,
            can1 = 9u, can2 = 9u, tim12 = 9u, tim13 = 9u, tim14 = 9u,
            otg_fs = 10u, otg_hs = 10u,
            eth = 11u,
            fsmc = 12u, otg_hs_fs = 12u, sdio = 12u,
            dcmi = 13u,
            eventout = 15u,
        };
    }
}
#endif // STM32TYPES_H
