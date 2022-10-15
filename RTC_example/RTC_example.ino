/**
 * FreeRTOS RTC Routine
 * Date: October 15, 2022
 * Author: Julio de Souza
  */

#include <stdlib.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include <time.h>
#include <ESP32Time.h>

// Use only core 1 for demo purposes
#if CONFIG_FREERTOS_UNICORE
  static const BaseType_t app_cpu = 0;
#else
  static const BaseType_t app_cpu = 1;
#endif
//Variables 
String hour_time = String(50);
// Settings
ESP32Time rtc(3600);
// Pins
static const int led_pin = LED_BUILTIN;
// Tasks

void Print_Time(void *parameters){
  int counter  = 0;
  int counter2 = 0;
  while(1){
    
    counter ++;
    counter2++;
    if (counter>200000){
        counter = 0;
        counter2 = 0;
        hour_time = rtc.getTime();
        Serial.println(hour_time);
      }
    }
    
  }

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
// Setup

void setup() {
  Serial.begin(115200);
  
  rtc.setTime(30, 24, 15, 17, 1, 2022); 

  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            Print_Time,      // Function to be called
            "Print Time",   // Name of task
            1024,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority
            NULL,           // Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)
              
}
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

void loop() {
  // put your main code here, to run repeatedly:

}
