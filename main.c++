//teste de David

#include <WiFi.h>
const char* targetSSID = "InternetNet";
const char * password= "abcdefgh";
int motorPin = 2;
const int rssiThreshold = -80;
int indice=0;
bool redeEncontrada = false;


void setup() {
  Serial.begin(115200);
  pinMode(motorPin, OUTPUT);
  analogWrite(motorPin, 0);
  WiFi.mode(WIFI_STA);
  WiFi.begin(targetSSID,password);
  while(WiFi.status() != WL_CONNECTED){
    Serial.print('.');
    delay(1000);
  }
  redeEncontrada = true;
}

void loop() {
  int rssi=WiFi.RSSI();

  if (rssi <= rssiThreshold) {
    analogWrite(motorPin, 0);
    Serial.println("SINAL MUITO FRACO → MOTOR DESLIGADO");
    Serial.println(rssi);
  } 
  else if (rssi > rssiThreshold && rssi <= -60) {
    analogWrite(motorPin, 85);
    Serial.println(rssi);
    Serial.println("CELULAR DISTANTE → VIBRAÇÃO FRACA");
  } 
  else if (rssi > -60 && rssi <= -40) {
    analogWrite(motorPin, 50);
    Serial.println(rssi);
    Serial.println("CELULAR PRóXIMO → VIBRAÇÃO MÉDIA");
  } 
  else { // rssi > -40 (mais perto de 0)
    analogWrite(motorPin, 1);
    Serial.println(rssi);
    Serial.println("CELULAR MUITO PROXIMO → VIBRAÇÃO FORTE"); 
  }
  if (!redeEncontrada) {
    analogWrite(motorPin, 0);
    Serial.println("Rede não encontrada. MOTOR DESLIGADO");
  }
  delay(1000);

}
