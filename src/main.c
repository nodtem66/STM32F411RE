//
// This file is part of the GNU ARM Eclipse distribution.
// Copyright (c) 2014 Liviu Ionescu.
//

// ----------------------------------------------------------------------------

#include <stdio.h>
#include "diag/Trace.h"
#include "BlinkLed.h"

// ----------------------------------------------------------------------------
//
// STM32F4 led blink sample (trace via ITM).
//
// In debug configurations, demonstrate how to print a greeting message
// on the trace device. In release configurations the message is
// simply discarded.
//
// To demonstrate POSIX retargetting, reroute the STDOUT and STDERR to the
// trace device and display messages on both of them.
//
// Then demonstrates how to blink a led with 1Hz, using a
// continuous loop and SysTick delays.
//
// On DEBUG, the uptime in seconds is also displayed on the trace device.
//
// Trace support is enabled by adding the TRACE macro definition.
// By default the trace messages are forwarded to the ITM output,
// but can be rerouted to any device or completely suppressed, by
// changing the definitions required in system/src/diag/trace_impl.c
// (currently OS_USE_TRACE_ITM, OS_USE_TRACE_SEMIHOSTING_DEBUG/_STDOUT).
//

/* Private function prototypes -----------------------------------------------*/

// ----- main() ---------------------------------------------------------------

// Sample pragmas to cope with warnings. Please note the related line at
// the end of this function, used to pop the compiler diagnostics status.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wmissing-declarations"
#pragma GCC diagnostic ignored "-Wreturn-type"

int main(void)
{
  // By customising __initialize_args() it is possible to pass arguments,
  // for example when running tests with semihosting you can pass various
  // options to the test.
  // trace_dump_args(argc, argv);

  // Send a greeting to the trace device (skipped on Release).
  trace_puts("Hello ARM World!");

  // The standard output and the standard error should be forwarded to
  // the trace device. For this to work, a redirection in _write.c is
  // required.
  puts("Standard output message.");
  fprintf(stderr, "Standard error message.\n");

  // At this stage the system clock should have already been configured
  // at high speed.
  //trace_printf("System clock: %uHz\n", SystemCoreClock);

  //timer_start();
  HAL_Init();
  blink_led_init();
  
  HAL_NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_0);
  HAL_NVIC_SetPriority(SysTick_IRQn, 0, 0);
  blink_led_off();
  // Infinite loop
  while (1)
    {
      blink_led_on();
      HAL_Delay(1000);
      //timer_sleep(BLINK_ON_TICKS);
      //delay(1000U);
      blink_led_off();
      //timer_sleep(BLINK_OFF_TICKS);
      HAL_Delay(1000);
      // Count seconds on the trace device.
      trace_printf("Second\n");
    }
  // Infinite loop, never return.
}



// ----------------------------------------------------------------------------
