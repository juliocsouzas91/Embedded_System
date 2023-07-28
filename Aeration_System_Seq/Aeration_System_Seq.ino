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
#define motor_controler 5
#define time_seep 60000000
#define button_on_pin 14
#define button_off_pin 12
#define overflow_timer_value 72*60

int *p_on, *p_off;
int operation_status;
int minutos_on, minutos_off;


void sleep(int *time_counter){
  esp_light_sleep_start();
  *time_counter =*time_counter+1;
}

void turn_on_motor(){
  digitalWrite(motor_controler, HIGH);
}

void turn_off_motor(){
  digitalWrite(motor_controler, LOW);
}

void IRAM_ATTR start_motor_button_int1(){
  *p_off = overflow_timer_value;
  *p_on = 0;
}

void IRAM_ATTR stop_motor_button_int2(){
  *p_on = overflow_timer_value;
  *p_off = 0;
}

void setup() {
  Serial.begin(115200);
  pinMode(motor_controler, OUTPUT);
	pinMode(button_off_pin, INPUT_PULLUP); //No pino, a leitura sempre será 1 e o botão joga para 0 ao ser pressionado. 
  p_on = &minutos_on;
  p_off = &minutos_off;
  *p_on = 0;
  *p_off = 0;
  esp_sleep_enable_timer_wakeup(time_seep); // Define o tempo dormindo
  operation_status = 0;
}

void loop() {
  switch(operation_status){
    case 0:
      if(*p_off<5){
        sleep(p_off);
      }
      else{
        attachInterrupt(button_off_pin, start_motor_button_int1, FALLING);
        operation_status = 1;
      }
    break;

    case 1:
      if(*p_off<30){
        sleep(p_off);
      }
      else{
        turn_on_motor();
        detachInterrupt(button_off_pin);
        attachInterrupt(button_off_pin, stop_motor_button_int2, FALLING);
        operation_status = 2;
      }
    break;
    case 2:
      if(*p_on<45){
        sleep(p_on);
      }
      else{
        *p_on = 0;
        *p_off = 0;
        detachInterrupt(button_off_pin);
        turn_off_motor();
        operation_status = 0;
      }
    break;
    default:
      delay(200);
  }
}