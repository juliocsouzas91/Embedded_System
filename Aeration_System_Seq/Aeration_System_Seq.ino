/*
80 MHz (ESP32_DEFAULT_CPU_FREQ_80)
160 MHz (ESP32_DEFAULT_CPU_FREQ_160)
240 MHz (ESP32_DEFAULT_CPU_FREQ_240)
*/
#define CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ ESP32_DEFAULT_CPU_FREQ_80
#define LED 2
#define time_seep 15000000

int status_on = 1;
int LED_status = 0;
uint64_t time_sleeping = 10000;
int minutos_on, minutos_off;
int *p_on, *p_off;
int operation_status = 0;

void sleep(int *time_counter){
  esp_light_sleep_start();
  time_counter ++;
}

void turn_on_motor(){
//Set 1 pin to turn on motor
}

void turn_off_motor(){
//Set 0 pin to turn off motor
}

void start_motor_button_int1(){
  *minutos_off = 72;
}

void stop_motor_button_int2(){
  *minutos_on = 72;
}

void setup() {
  p_on = &minutos_on;
  p_off = &minutos_off;
  pinMode(LED, OUTPUT);
  Serial.begin(115200);
  esp_sleep_enable_timer_wakeup(time_seep); //1 second
  *p_on = 0;
  *p_off = 0;

}

void loop() {
  switch(operation_status){
    case 0:
    if(*p_on<15){
      sleep(p_off);
    }
    else{
      //Enable Int1
      operation_status ++;
    }
    break;

    case 1:
    if(*p_on<60){
      sleep(p_off);
    }
    else{
      turn_on_motor()
      //Habilita a Int2
      operation_status ++;
    }
    break;
    case 2:
      if(*p_on<30){
        sleep(p_on);
      }
      else{
        *p_on = 0;
        *p_off = 0;
        //Disble Int1
        //Disable Int2
        //Turn Off Motor
        operation_status = 0;
      }
    break;
    default
        turn_off_motor();
  }
}