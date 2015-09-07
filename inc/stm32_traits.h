#ifndef STM32_TRAITS_H
#define STM32_TRAITS_H

#include "stm32_types.h"

#include <type_traits>

namespace ecpp {
namespace stm32 {

/**
 * @brief Type trait for checking if a Timer_e value is a basic timer.
 */
template<Timer_e>
struct is_basic : std::false_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER6 is a basic timer.
 */
template<>
struct is_basic<Timer_e::TIMER6> : std::true_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER7 is a basic timer.
 */
template<>
struct is_basic<Timer_e::TIMER7> : std::true_type {};

/**
 * @brief Type trait for checking if a Timer_e value is a general purpose timer.
 */
template<Timer_e>
struct is_general_purpose : std::false_type {};

// TODO: Add type traits for general purpose timers.

/**
 * @brief Type trait for checking if a Timer_e value is an advanced control timer.
 */
template<Timer_e>
struct is_advanced_control : std::false_type {};

// TODO: Add type traits for advanced control timers.

/**
 * @brief Type trait for checking if a Timer_e value is capable of generating DMA requests.
 */
template<Timer_e>
struct is_dmarq_capable : std::false_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER6 is capable of generating DMA requests.
 */
template<>
struct is_dmarq_capable<Timer_e::TIMER6> : std::true_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER7 is capable of generating DMA requests.
 */
template<>
struct is_dmarq_capable<Timer_e::TIMER7> : std::true_type {};

// TODO: Add type traits for dmarq capable timers.

/**
 * @brier Type trait for checking if a Timer_e value is a 32bit timer.
 */
template<Timer_e>
struct is_32bit : std::false_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER2 is a 32bit timer.
 */
template<>
struct is_32bit<Timer_e::TIMER2> : std::true_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER5 is a 32bit timer.
 */
template<>
struct is_32bit<Timer_e::TIMER5> : std::true_type {};

/**
 * @brier Type trait for checking if a Timer_e value is multidirectional.
 */
template<Timer_e>
struct is_multidir : std::false_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER1 is a multidirectional timer.
 */
template<>
struct is_multidir<Timer_e::TIMER1> : std::true_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER2 is a multidirectional timer.
 */
template<>
struct is_multidir<Timer_e::TIMER2> : std::true_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER3 is a multidirectional timer.
 */
template<>
struct is_multidir<Timer_e::TIMER3> : std::true_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER4 is a multidirectional timer.
 */
template<>
struct is_multidir<Timer_e::TIMER4> : std::true_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER5 is a multidirectional timer.
 */
template<>
struct is_multidir<Timer_e::TIMER5> : std::true_type {};

/**
 * @brief Type trait confirming that Timer_e::TIMER8 is a multidirectional timer.
 */
template<>
struct is_multidir<Timer_e::TIMER8> : std::true_type {};

} // end of ecpp::stm32

/**
 * @brief Type trait confirming that TimerIrq_e is a bitmask.
 */
template<>
struct is_bitmask<ecpp::stm32::TimerIrq_e> : std::true_type {};

/**
 * @brief Type trait confirming that TimerDmarq_e is a bitmask.
 */
template<>
struct is_bitmask<ecpp::stm32::TimerDmarq_e> : std::true_type {};

} // end of ecpp

#endif // STM32_TRAITS_H
