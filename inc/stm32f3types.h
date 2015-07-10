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

#ifndef STM32F3TYPES_H
#define STM32F3TYPES_H

#ifdef stm32f3

#include "stm32f3xx.h"

#include <cstdint>

namespace ecpp {
    namespace stm32 {

        enum class ahbenr : std::uint32_t {
            gpioa = RCC_AHBENR_GPIOAEN,
            gpiob = RCC_AHBENR_GPIOBEN,
            gpioc = RCC_AHBENR_GPIOCEN,
            gpiod = RCC_AHBENR_GPIODEN,
            gpioe = RCC_AHBENR_GPIOEEN,
            gpiof = RCC_AHBENR_GPIOFEN,
            // TODO: add other peripheral bits
        };

        template<ahbenr... M>
        struct ahbenr_mask;

        template<>
        struct ahbenr_mask<> {
            static constexpr std::uint32_t value = 0;
        };

        template<ahbenr first, ahbenr... rest>
        struct ahbenr_mask<first, rest...> {
            static constexpr std::uint32_t value = static_cast<std::uint32_t>(first) | ahbenr_mask<rest...>::value;
        };
    }
}

#endif

#endif // STM32F3TYPES_H
