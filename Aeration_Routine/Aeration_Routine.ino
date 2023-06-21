/**
 * Aering System Routine
 * Date: October 20, 2022
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
  hw_timer_t *My_timer = NULL;
  int time_diference;
// Settings
  xTaskHandle TaskHandle_RTC;
  ESP32Time rtc(0);

// Pins
  static const int led_pin = LED_BUILTIN;

// Tasks

void IRAM_ATTR onTimer(){
  vTaskResume(TaskHandle_RTC);
}
/*
void create_number_from_char_time(String *char_time){
  int time_sec = 0, time_dec = 0, total_time = 0;
  time_sec = *(char_time+7).toInt();
  time_dec = *(char_time+6)+0;
  total_time = time_dec*10+time_sec;
  Serial.Prinln(total_time)
}*/
void Print_Time(void *parameters){
  int tempo = 0;
  while(1){
    hour_time = rtc.getTime();
    hour_time.remove(0,6);
    tempo = hour_time.toInt();
    //Serial.println(tempo);
    if (tempo==0){
      Serial.println("Chuva nessa porra"); //Toogle a pin in this
    }
    //create_number_from_char_time(&hour_time);
    vTaskSuspend(TaskHandle_RTC);
   }
  }

/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/
// Setup

void setup() {
  Serial.begin(115200);
  
  rtc.setTime(0, 15, 39, 17, 1, 2022); 

  xTaskCreatePinnedToCore(  // Use xTaskCreate() in vanilla FreeRTOS
            Print_Time,      // Function to be called
            "Print Time",   // Name of task
            2048,           // Stack size (bytes in ESP32, words in FreeRTOS)
            NULL,           // Parameter to pass
            1,              // Task priority
            &TaskHandle_RTC,// Task handle
            app_cpu);       // Run on one core for demo purposes (ESP32 only)
  My_timer = timerBegin(0, 80, true);
  timerAttachInterrupt(My_timer, &onTimer, true);
  timerAlarmWrite(My_timer, 1000000, true);
  timerAlarmEnable(My_timer); //Just Enable            
}
/*xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx*/

void loop() {
  // put your main code here, to run repeatedly:

}
