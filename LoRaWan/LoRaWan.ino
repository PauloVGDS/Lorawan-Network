/*
 * Função:
 * 1. * 1. Envia um pacote de dados para o servidor, usando o modelo padrão do protocolo LoRaWan.
 *  
 * Descrição:
 * 1. Comunicação usando o protocolo LoRaWan.
 *
 * */

#include "LoRaWan_APP.h"
#include "max6675.h"

// Fator de conversão de microsegundos para segundos 
#define mS_TO_S_FACTOR 1000
// Fator de conversão de segundos para minutos
#define s_TO_MIN_FACTOR 60
// Tempo que o ESP32 ficará em modo sleep (em minutos)
#define CYCLE_SLEEP 15

#define pinSO 0   //PINO DIGITAL (SO)
#define pinCS 1   //PINO DIGITAL (CS)
#define pinCLK 2  //PINO DIGITAL (CLK / SCK)
MAX6675 sensorTemp(pinCLK, pinCS, pinSO);

/* OTAA(Over the Air Activation) para*/
uint8_t devEui[] = { 0x38, 0x05, 0x18, 0x8F, 0xFF, 0xFF, 0xFF, 0xFF };                                               
uint8_t appEui[] = { 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF };                                                  // JoinEUI FF000000000000FF
uint8_t appKey[] = { 0xED, 0xA4, 0x16, 0xFC, 0x3B, 0xEE, 0x03, 0x51, 0x2C, 0x02, 0x3B, 0x8D, 0x67, 0x06, 0x67, 0xD9 };  // AppKey EDA416FC3BEE03512C023B8D670667D9
/* ABP(Activation By Personalization) para*/
uint8_t nwkSKey[] = { 0x15, 0xB1, 0xD0, 0xEF, 0xA4, 0x63, 0xDF, 0xBE, 0x3D, 0x11, 0x18, 0x1E, 0x1E, 0xC7, 0xDA, 0x85 };
uint8_t appSKey[] = { 0xd7, 0x2c, 0x78, 0x75, 0x8c, 0xdc, 0xca, 0xbf, 0x55, 0xee, 0x4a, 0x77, 0x8d, 0x16, 0xef, 0x67 };
uint32_t devAddr = (uint32_t)0x007e6ae1;

/*LoraWan mascara de canal, default channels 0-7*/
uint16_t userChannelsMask[6] = { 0xFFFF, 0xFFFF, 0xFFFF };

/*Região LoraWan, US915E6/AU915 permitido no Brasil*/
LoRaMacRegion_t loraWanRegion = ACTIVE_REGION;
/*LoraWan Class, Class A e Class C são suportados*/
DeviceClass_t loraWanClass = CLASS_A;
//O Duty Cicle da aplicação. Valores em [ms].
uint32_t appTxDutyCycle = (mS_TO_S_FACTOR * s_TO_MIN_FACTOR) * CYCLE_SLEEP;
/*OTAA or ABP*/
bool overTheAirActivation = true;
/*ADR ativo(Adaptative Data Ratio)*/
bool loraWanAdr = true;
/* Indicates if the node is sending confirmed or unconfirmed messages */
bool isTxConfirmed = true;
uint8_t appPort = 2;            // Identificador númerico usado para diferenciar os tipos de dados enviados*/
uint8_t confirmedNbTrials = 8;  // Número de Tentativas de transmissão antes de desistir

/* Prepares the payload of the frame */
static void prepareTxFrame(uint8_t port) {
  /*appData size is LORAWAN_APP_DATA_MAX_SIZE which is defined in "commissioning.h".
  *appDataSize max value is LORAWAN_APP_DATA_MAX_SIZE.
  */
  /*Serial.print(sensorTemp.readCelsius());
  Serial.println("c");
  delay(1000);    
*/
 appDataSize = 4;
 
  unsigned char *puc;
  appDataSize = 0;
  int tempCelsius = sensorTemp.readCelsius();  
  puc = (unsigned char *)(&tempCelsius);   
  Serial.println(tempCelsius);     

  appData[appDataSize++] = puc[0];
  appData[appDataSize++] = puc[1];
  appData[appDataSize++] = puc[2];
  appData[appDataSize++] = puc[3];
}

void setup() {
  Serial.begin(115200);
  Mcu.begin(HELTEC_BOARD, SLOW_CLK_TPYE);
  Serial.println("Setup pronto!");
  delay(100);
}

void loop() {
  switch (deviceState) {
    case DEVICE_STATE_INIT:
      {
        #if (LORAWAN_DEVEUI_AUTO)
          LoRaWAN.generateDeveuiByChipID();
        #endif
        LoRaWAN.init(loraWanClass, loraWanRegion);
        //both set join DR and DR when ADR off
        LoRaWAN.setDefaultDR(3);
        Serial.println("Lora iniciado!");
        break;
      }
    case DEVICE_STATE_JOIN:
      {
        LoRaWAN.join();
        break;
      }
    case DEVICE_STATE_SEND:
      {
        //Serial.println("Join Aceito");
        //Serial.println("Enviando informações");
        prepareTxFrame(appPort);
        LoRaWAN.send();
        //Serial.println("Informações enviadas!");
        deviceState = DEVICE_STATE_CYCLE;
        break;
      }
    case DEVICE_STATE_CYCLE:
    {
      // Agendar a transmissão do próximo pacote
      txDutyCycleTime = appTxDutyCycle + randr( -APP_TX_DUTYCYCLE_RND, APP_TX_DUTYCYCLE_RND );
      LoRaWAN.cycle(txDutyCycleTime);
      deviceState = DEVICE_STATE_SLEEP;
      break;
    }
    case DEVICE_STATE_SLEEP:
    {
      LoRaWAN.sleep(loraWanClass);
      break;
    }
    default:
      {
      deviceState = DEVICE_STATE_INIT;
      break;
     }
  }
}
