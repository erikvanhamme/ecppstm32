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

#ifndef RCC_H
#define RCC_H

#include "stm32types.h"

#include "stm32f4xx.h"

#include <cstdint>

namespace ecpp {
    namespace stm32 {
        namespace rcc {

            template<ahb1enr... M>
            static void enableClock() {
                RCC->AHB1ENR |= ahb1enr_mask<M...>::value;
            }

            template<ahb1enr... M>
            static void disableClock() {
                RCC->AHB1ENR &= ~ahb1enr_mask<M...>::value;
            }
        }
    }
}
#endif // RCC_H
