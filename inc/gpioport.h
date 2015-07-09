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

#ifndef GPIOPORT_H
#define GPIOPORT_H

#include "rcc.h"
#include "stm32types.h"

#include "stm32f4xx.h"

#include <cstdint>

namespace ecpp {
    namespace stm32 {
        template <gpioport P>
        class GpioPort final {
        public:

            static void enable() {
                switch(P) {
                case gpioport::pa:
                    rcc::enableClock<ahb1enr::gpioa>();
                    break;
                case gpioport::pb:
                    rcc::enableClock<ahb1enr::gpiob>();
                    break;
                case gpioport::pc:
                    rcc::enableClock<ahb1enr::gpioc>();
                    break;
                case gpioport::pd:
                    rcc::enableClock<ahb1enr::gpiod>();
                    break;
                case gpioport::pe:
                    rcc::enableClock<ahb1enr::gpioe>();
                    break;
                case gpioport::pf:
                    rcc::enableClock<ahb1enr::gpiof>();
                    break;
                case gpioport::pg:
                    rcc::enableClock<ahb1enr::gpiog>();
                    break;
                case gpioport::ph:
                    rcc::enableClock<ahb1enr::gpioh>();
                    break;
                case gpioport::pi:
                    rcc::enableClock<ahb1enr::gpioi>();
                    break;
                }
            }

            static void disable() {
                switch(P) {
                case gpioport::pa:
                    rcc::disableClock<ahb1enr::gpioa>();
                    break;
                case gpioport::pb:
                    rcc::disableClock<ahb1enr::gpiob>();
                    break;
                case gpioport::pc:
                    rcc::disableClock<ahb1enr::gpioc>();
                    break;
                case gpioport::pd:
                    rcc::disableClock<ahb1enr::gpiod>();
                    break;
                case gpioport::pe:
                    rcc::disableClock<ahb1enr::gpioe>();
                    break;
                case gpioport::pf:
                    rcc::disableClock<ahb1enr::gpiof>();
                    break;
                case gpioport::pg:
                    rcc::disableClock<ahb1enr::gpiog>();
                    break;
                case gpioport::ph:
                    rcc::disableClock<ahb1enr::gpioh>();
                    break;
                case gpioport::pi:
                    rcc::disableClock<ahb1enr::gpioi>();
                    break;
                }
            }

            static std::uint32_t get() {
                return _gpio->IDR;
            }

            static void set(std::uint32_t value) {
                _gpio->ODR = value;
            }

            template<gpiopin... M>
            static void high() {
                _gpio->ODR |= gpiopin_mask<M...>::value;
            }

            template<gpiopin... M>
            static void low() {
                _gpio->ODR &= ~gpiopin_mask<M...>::value;
            }

        private:
            static constexpr GPIO_TypeDef *_gpio = reinterpret_cast<GPIO_TypeDef *> (P);
        };
    }
}

#endif // GPIOPORT_H
