#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <Espalexa.h>

// Definições
#define pinActive 0

const char* SSID = "NOME_REDE";
const char* PASSWD = "SENHA_REDE";

Espalexa espalexa;

// Funções Bult-In
boolean connectWifi();

void controlerQuintal(uint8_t brightness);

void setup() {

    Serial.begin(115200);

	pinMode(LED_BUILTIN, OUTPUT);
    pinMode(pinActive, OUTPUT);

    boolean wifiConnected = connectWifi();

    if (wifiConnected) {
        espalexa.addDevice("OPA", controlerQuintal);
        espalexa.begin();
    } else {
        while (1) {
            Serial.println("Não foi possível conectar no WiFi.");
            delay(2500);
        }
    }
  
}

void led() {
	digitalWrite(LED_BUILTIN, HIGH);
  	Serial.println("ON");
  	delay(500);
  	digitalWrite(LED_BUILTIN, LOW);
  	Serial.println("OFF");
  	delay(500);
}

void loop() {
	//led();
	espalexa.loop();
    delay(1);
}

// Verifica se a conexão com o WiFi foi bem sucedida 
boolean connectWifi() {

    boolean state = true;
    int i = 0;

    WiFi.mode(WIFI_STA);
    WiFi.begin(SSID, PASSWD);

    Serial.println("Conectando no WiFi...");

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
        if (i > 20) {
            state = false;
            break;
        }
        i++;
    }
    return state;

}

void controlerQuintal(uint8_t brightness) {
    if (brightness == 255) {
        digitalWrite(pinActive, HIGH);
        Serial.println("Quintal ON");
    } else {
        digitalWrite(pinActive, LOW);
        Serial.println("Quintal OFF");
    }
}