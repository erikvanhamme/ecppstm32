#ifndef STM32_TRAITS_H
#define STM32_TRAITS_H

#include "stm32_types.h"

#include <type_traits>

namespace ecpp {
namespace stm32 {

template<Timer_e>
struct is_basic : std::false_type {};

template<>
struct is_basic<Timer_e::TIMER6> : std::true_type {};

template<>
struct is_basic<Timer_e::TIMER7> : std::true_type {};

template<Timer_e>
struct is_general_purpose : std::false_type {};

// TODO: Add type traits for general purpose timers.

template<Timer_e>
struct is_advanced_control : std::false_type {};

// TODO: Add type traits for advanced control timers.

template<Timer_e>
struct is_dmarq : std::false_type {};

template<>
struct is_dmarq<Timer_e::TIMER6> : std::true_type {};

template<>
struct is_dmarq<Timer_e::TIMER7> : std::true_type {};

// TODO: Add type traits for dmarq capable timers.

} // end of ecpp::stm32

template<>
struct is_bitmask<ecpp::stm32::TimerIrq_e> : std::true_type {};

template<>
struct is_bitmask<ecpp::stm32::TimerDmarq_e> : std::true_type {};

} // end of ecpp

#endif // STM32_TRAITS_H
