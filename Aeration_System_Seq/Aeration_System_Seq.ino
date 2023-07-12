/**Rotina de aeração, flowchart do programa pode ser encontrado em:
https://app.diagrams.net/#Hjuliocsouzas91%2FEmbedded_System%2Faeration_system%2FAeration_System_Seq%2FAerationSystem.drawio
Autores: Julio Souza e Neudes...
/
/*
80 MHz (ESP32_DEFAULT_CPU_FREQ_80)
160 MHz (ESP32_DEFAULT_CPU_FREQ_160)
240 MHz (ESP32_DEFAULT_CPU_FREQ_240)
*/
#define CONFIG_ESP32_DEFAULT_CPU_FREQ_MHZ ESP32_DEFAULT_CPU_FREQ_80
#define motor_controler 32
#define time_seep 15000000
#define button_on_pin 36
#define button_off_pin 39
#define overflow_timer_value 72

int *p_on, *p_off;
int status_on = 1;
int LED_status = 0;
int operation_status = 0;
int minutos_on, minutos_off;
uint64_t time_sleeping = 10000;



void sleep(int *time_counter){
  esp_light_sleep_start();
  time_counter ++;
}

void turn_on_motor(){
  digitalWrite(motor_controler, 1);
}

void turn_off_motor(){
  digitalWrite(motor_controler, 0);
}

void IRAM_ATTR start_motor_button_int1(){
  *p_off = overflow_timer_value;
}

void IRAM_ATTR stop_motor_button_int2(){
  *p_on = overflow_timer_value;
}

void setup() {
  pinMode(motor_controler, OUTPUT);
  pinMode(button_on_pin, INPUT_PULLDOWN); //No pino a leitura sempre será 0 e o botão joga para 1 a ser pressionado 
	pinMode(button_off_pin, INPUT_PULLUP); //No pino, a leitura sempre será 1 e o botão joga para 0 ao ser pressionado. 
  Serial.begin(115200);
  p_on = &minutos_on;
  p_off = &minutos_off;
  *p_on = 0;
  *p_off = 0;
  esp_sleep_enable_timer_wakeup(time_seep); // Define o tempo dormindo
}

void loop() {
  switch(operation_status){
    case 0:
      if(*p_off<15){
        sleep(p_off);
      }
      else{
        attachInterrupt(button_on_pin, start_motor_button_int1, RISING);
        operation_status ++;
      }
    break;

    case 1:
      if(*p_off<60){
        sleep(p_off);
      }
      else{
        turn_on_motor();
        attachInterrupt(button_off_pin, stop_motor_button_int2, FALLING);
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
        detachInterrupt(button_on_pin);
        detachInterrupt(button_off_pin);
        turn_off_motor();
        operation_status = 0;
      }
    break;
    default:
        turn_off_motor();
  }
}