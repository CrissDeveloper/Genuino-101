#include <CurieBLE.h>

BLEPeripheral blePeripheral; 
BLEService Controle_LED("42e9bbe84ba2489cbc8cde95a70dbf30"); //19B10000-E8F2-537E-4F6C-D104768A1214

BLEUnsignedCharCharacteristic switchCharacteristic1("19B10001-E8F2-537E-4F6C-D104768A1214", BLERead | BLEWrite);

#define ledPin1 13 //Pino Led 1
//#define ledPin2 7 //Pino Led 2

void setup() {
  Serial.begin(9600);
  //define os pinos dos leds como saida
  pinMode(ledPin1, OUTPUT);
  //pinMode(ledPin2, OUTPUT);

  // set advertised local name and service UUID:
  blePeripheral.setLocalName("Genuino_LED");
  blePeripheral.setAdvertisedServiceUuid(Controle_LED.uuid());

  // add service and characteristic:
  blePeripheral.addAttribute(Controle_LED);
  blePeripheral.addAttribute(switchCharacteristic1);

  // set the initial value for the characeristic:
  switchCharacteristic1.setValue(0);

  // begin advertising BLE service:
  blePeripheral.begin();

  Serial.print("BLE LED com Genuino 101");
}

void loop() {
  //Aguarda a conexão por Blutooth
  BLECentral central = blePeripheral.central();

  //Se ocorrer a conexão
  if (central) {
    Serial.print("Conectado a central: ");
    //Mostra o MAC address do dispositivo conectado
    Serial.println(central.address());

    //Executa enquanto o dispositivo estiver conectado
    while (central.connected()) {
      //Aguarda o valor enviadoplelo dispositivo conectado e aciona o led correspondente
      if (switchCharacteristic1.written()) {
        //Caso receba o valor 1, aciona o led 1
        if (switchCharacteristic1.value() == 1) {
          Serial.println("LED 1 ligado");
          digitalWrite(ledPin1, HIGH);
        }

        /*//Caso receba o valor 2, aciona o led 2
        if (switchCharacteristic1.value() == 2) {
          Serial.println("LED 2 ligado");
          digitalWrite(ledPin2, HIGH);
        }*/

        //Caso receba o valor 0, apaga todos os leds
        if (switchCharacteristic1.value() == 0) {
          Serial.println(F("LEDs desligados"));
          digitalWrite(ledPin1, LOW);
          //digitalWrite(ledPin2, LOW);
        }
      }
    }
  }

  //Quando ocorrer desconexão, mostra mensagem
  Serial.print(F("Desconectado da central: "));
  Serial.println(central.address());
}
