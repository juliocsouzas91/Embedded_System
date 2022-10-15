/**
 * FreeRTOS RTC example
 * 
 * 
 * 
 * Date: October 15, 2022
 * Author: Julio de Souza
 * License: 0BSD
 */

#include <stdlib.h>

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif

// Settings
static const uint8_t buf_len = 20;

// Pins
static const int led_pin = LED_BUILTIN;

// Globals
static long int led_delay = 500;   // ms
//*****************************************************************************
// Tasks

// Setup
void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
