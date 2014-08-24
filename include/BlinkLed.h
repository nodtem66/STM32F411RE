//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

#ifndef BLINKLED_H_
#define BLINKLED_H_

#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

// ----- LED definitions ------------------------------------------------------

// Adjust these definitions for your own board.

// STM32F411RE6 definitions (the LD2 USER LED PA_5, active high)

#define BLINK_PORT_NUMBER               (0)
#define BLINK_PIN_NUMBER                (5)
#define BLINK_ACTIVE_LOW                (0)


#define BLINK_GPIOx(_N)                 ((GPIO_TypeDef *)(GPIOA_BASE + (GPIOB_BASE-GPIOA_BASE)*(_N)))
#define BLINK_PIN_MASK(_N)              (1 << (_N))
#define BLINK_RCC_MASKx(_N)             (RCC_AHB1ENR_GPIOAEN << (_N))

// ----------------------------------------------------------------------------

extern
void
blink_led_init(void);

// ----------------------------------------------------------------------------

inline void
blink_led_on(void);

inline void
blink_led_off(void);

// ----------------------------------------------------------------------------

inline void
__attribute__((always_inline))
blink_led_on(void)
{
#if (BLINK_ACTIVE_LOW)
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_RESET);
#else
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_SET);
#endif
}

inline void
__attribute__((always_inline))
blink_led_off(void)
{
#if (BLINK_ACTIVE_LOW)
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_SET);
#else
    HAL_GPIO_WritePin(BLINK_GPIOx(BLINK_PORT_NUMBER),
        BLINK_PIN_MASK(BLINK_PIN_NUMBER), GPIO_PIN_RESET);
#endif
}

// ----------------------------------------------------------------------------

#endif // BLINKLED_H_
