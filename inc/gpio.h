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

#ifndef GPIO_H
#define GPIO_H

#include "rcc.h"
#include "utils.h"

#ifdef stm32f3
#include "stm32f3xx.h"
#endif

#ifdef stm32f4
#include "stm32f4xx.h"
#endif

#include <cstdint>
#include <type_traits>

namespace ecpp {
    namespace stm32 {

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

        enum class gpiomode {
            input_floating = 0,       // Floating Input       (MODE=00 TYPE=0 PUP=00)
            input_pullup = 1,         // Pullup Input         (MODE=00 TYPE=0 PUP=01)
            input_pulldown = 2,       // Pulldown Input       (MODE=00 TYPE=0 PUP=10)
            input_analog = 24,        // Analog Input         (MODE=11 TYPE=0 PUP=00)
            output_pushpull = 8,      // Push Pull Output     (MODE=01 TYPE=0 PUP=00)
            output_opendrain = 12,    // Open Drain Output    (MODE=01 TYPE=1 PUP=00)
            alternate = 16,           // Alternate function   (MODE=10 TYPE=0 PUP=00)
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

        class GpioPinBase {
        protected:

            static void configureImpl(GPIO_TypeDef &port, unsigned int mode, unsigned int pin) {
                port.MODER  &= ~(3 << (pin * 2));
                port.OTYPER &= ~(1 << pin);
                port.PUPDR  &= ~(3 << (pin * 2));

                port.MODER  |= (mode >> 3) << (pin * 2);
                port.OTYPER |= ((mode >> 2) & 1) << pin;
                port.PUPDR  |= (mode & 3) << (pin * 2);
            }

            static void alternateImpl(GPIO_TypeDef &port, unsigned int af, unsigned int pin) {

                if(pin < 8) {
                    port.AFR[0] &= ~(0xf << (pin * 4));
                    port.AFR[0] |= af << (pin * 4);
                } else {
                    pin -= 8;
                    port.AFR[1] &= ~(0xf << (pin * 4));
                    port.AFR[1] |= af << (pin * 4);
                }
            }

        private:
            GpioPinBase() = delete;
        };

        // TODO: Investigate bit-banding for GPIO pins.
        template<gpioport Port, gpiopin Pin>
        class GpioPin final : public GpioPinBase {
        public:

            static void configure(gpiomode mode) {
                constexpr unsigned int pin = utils::bitPosition(static_cast<std::uint32_t>(Pin));
                configureImpl(*_gpio, static_cast<unsigned int>(mode), pin);
            }

            static void alternate(alternatefunction af) {
                constexpr unsigned int pin = utils::bitPosition(static_cast<std::uint32_t>(Pin));
                alternateImpl(*_gpio, static_cast<unsigned int>(af), pin);
            }

            static bool value() {
                return _gpio->IDR & static_cast<std::uint32_t>(Pin);
            }

            static void high() {
                // TODO: read datasheet to determine if it is better to use the bit set/reset register.
                _gpio->ODR |= static_cast<std::uint32_t>(Pin);
            }

            static void low() {
                // TODO: read datasheet to determine if it is better to use the bit set/reset register.
                _gpio->ODR &= ~static_cast<std::uint32_t>(Pin);
            }

            static void toggle() {
                // TODO: read datasheet to determine if it is better to use the bit set/reset register.
                _gpio->ODR ^= static_cast<std::uint32_t>(Pin);
            }

        private:
            static constexpr GPIO_TypeDef *_gpio = reinterpret_cast<GPIO_TypeDef *>(Port);

            GpioPin() = delete;
        };

        // TODO: Consider if the enable/disable methods are needed/wanted. Possible to clean up code if not needed.
        template <gpioport P>
        class GpioPort final {
        public:

            static void enable() {
#ifdef stm32f3
                switch(P) {
                case gpioport::pa:
                    rcc::enableClock<ahbenr::gpioa>();
                    break;
                case gpioport::pb:
                    rcc::enableClock<ahbenr::gpiob>();
                    break;
                case gpioport::pc:
                    rcc::enableClock<ahbenr::gpioc>();
                    break;
                case gpioport::pd:
                    rcc::enableClock<ahbenr::gpiod>();
                    break;
                case gpioport::pe:
                    rcc::enableClock<ahbenr::gpioe>();
                    break;
                case gpioport::pf:
                    rcc::enableClock<ahbenr::gpiof>();
                    break;
                }
#endif
#ifdef stm32f4
                switch(P) {
                case gpioport::pa:
                    rcc::enableClock(ahb1enr::gpioa);
                    break;
                case gpioport::pb:
                    rcc::enableClock(ahb1enr::gpiob);
                    break;
                case gpioport::pc:
                    rcc::enableClock(ahb1enr::gpioc);
                    break;
                case gpioport::pd:
                    rcc::enableClock(ahb1enr::gpiod);
                    break;
                case gpioport::pe:
                    rcc::enableClock(ahb1enr::gpioe);
                    break;
                case gpioport::pf:
                    rcc::enableClock(ahb1enr::gpiof);
                    break;
                case gpioport::pg:
                    rcc::enableClock(ahb1enr::gpiog);
                    break;
                case gpioport::ph:
                    rcc::enableClock(ahb1enr::gpioh);
                    break;
                case gpioport::pi:
                    rcc::enableClock(ahb1enr::gpioi);
                    break;
                }
#endif
            }

            static void disable() {
#ifdef stm32f3
                switch(P) {
                case gpioport::pa:
                    rcc::disableClock<ahbenr::gpioa>();
                    break;
                case gpioport::pb:
                    rcc::disableClock<ahbenr::gpiob>();
                    break;
                case gpioport::pc:
                    rcc::disableClock<ahbenr::gpioc>();
                    break;
                case gpioport::pd:
                    rcc::disableClock<ahbenr::gpiod>();
                    break;
                case gpioport::pe:
                    rcc::disableClock<ahbenr::gpioe>();
                    break;
                case gpioport::pf:
                    rcc::disableClock<ahbenr::gpiof>();
                    break;
                }
#endif
#ifdef stm32f4
                switch(P) {
                case gpioport::pa:
                    rcc::disableClock(ahb1enr::gpioa);
                    break;
                case gpioport::pb:
                    rcc::disableClock(ahb1enr::gpiob);
                    break;
                case gpioport::pc:
                    rcc::disableClock(ahb1enr::gpioc);
                    break;
                case gpioport::pd:
                    rcc::disableClock(ahb1enr::gpiod);
                    break;
                case gpioport::pe:
                    rcc::disableClock(ahb1enr::gpioe);
                    break;
                case gpioport::pf:
                    rcc::disableClock(ahb1enr::gpiof);
                    break;
                case gpioport::pg:
                    rcc::disableClock(ahb1enr::gpiog);
                    break;
                case gpioport::ph:
                    rcc::disableClock(ahb1enr::gpioh);
                    break;
                case gpioport::pi:
                    rcc::disableClock(ahb1enr::gpioi);
                    break;
                }
#endif
            }

            static std::uint32_t get() {
                return _gpio->IDR;
            }

            static void set(gpiopin pins) {
                _gpio->ODR = static_cast<std::uint32_t>(pins);
            }

            static void high(gpiopin pins) {
                _gpio->ODR |= static_cast<std::uint32_t>(pins);
            }

            static void low(gpiopin pins) {
                _gpio->ODR &= ~static_cast<std::uint32_t>(pins);
            }

        private:
            static constexpr GPIO_TypeDef *_gpio = reinterpret_cast<GPIO_TypeDef *> (P);
        };
    }

    template<>
    struct is_bitmask<ecpp::stm32::gpiopin> : std::true_type {};
}
#endif // GPIO_H
