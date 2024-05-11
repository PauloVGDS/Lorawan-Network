// Fator de conversão de microsegundos para segundos
#define uS_TO_S_FACTOR 1000000
// Fator de conversão de segundos para minutos
#define s_TO_MIN_FACTOR 60
// Tempo que o ESP32 ficará em modo sleep (em minutos)
#define TIME_TO_SLEEP 5

#define GPIO0 0

void setup() {
  Serial.begin(115200);
  delay(1000);
  // Despertar depois de um certo periodo
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP * uS_TO_S_FACTOR);
  //esp_deep_sleep_enable_timer_wakeup((uS_TO_S_FACTOR * s_TO_MIN_FACTOR) * TIME_TO_SLEEP)

  Serial.println("Entrando em modo sleep"); 
  esp_deep_sleep_start(); // Inicia o modo sleep

  Serial.println("Essa linha nunca será exibida!");
  }

void loop() {
  // put your main code here, to run repeatedly:

}
