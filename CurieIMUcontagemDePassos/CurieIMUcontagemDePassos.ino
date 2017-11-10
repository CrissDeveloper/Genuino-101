/* 
 * Copyright (c) 2016 Intel Corporation.  Todos os direitos reservados. 
 * Veja o final deste arquivo para os termos da licença. 
 */ 

 /* 
 Este exemplo demonstra como esboço do acelerômetro BMI160 na 
 Intel (R) Curie (TM) do módulo pode ser usado como um contador de passos (podómetro) 
 */ 

 #include "CurieIMU.h" 

 /* Para obter uma notificação de interrupção para cada passo detectado, 
 conjunto stepEventsEnabeled para true.  Caso contrário, o loop principal será 
 pesquisar para a contagem atual etapa. 

 Pelo projeto, o contador de passos não atualizar imediatamente em cada etapa detectado. 
 Consulte a Seção 2.7 da Folha de BMI160 IMU SensorData 
 Para mais informações sobre este recurso. 
 */
 
const int ledPin = 13;

boolean stepEventsEnabeled = true;   // se você é de votação ou usando eventos
long lastStepCount = 0;              // contagem de passos no check sondagem anterior
boolean blinkState = false;          // estado do LED

void setup() {
  Serial.begin(9600); // Inicializa comunicação serial
  while(!Serial) ;    // esperar por porta serial para conectar. 
 // PinMode (13, OUTPUT); 
 // Intialize o sensor:
  CurieIMU.begin();
  // Ativar o modo de detecção de passo:
  CurieIMU.setStepDetectionMode(CURIE_IMU_STEP_MODE_NORMAL);
  // Activar contagem passo:
  CurieIMU.setStepCountEnabled(true);

  if (stepEventsEnabeled) {
    // Anexar a função eventCallback como o 
    // Manipulador de eventos passo:
    CurieIMU.attachInterrupt(eventCallback);
    CurieIMU.interrupts(CURIE_IMU_STEP);  // Ligar a detecção de etapa

    Serial.println("IMU initialisation complete, waiting for events...");
  }
}

void loop() {
  /*Em vez de usar as notificações de eventos de detecção de  passo, podemos verificar a contagem de passos periodicamente*/
  if (!stepEventsEnabeled) {
    updateStepCount();
  }
  digitalWrite(13, blinkState);
  blinkState = !blinkState;
  delay(1000);
}

static void updateStepCount() {
  // Obter a contagem de passos:
  int stepCount = CurieIMU.getStepCount();

  // Se o contador de passos mudou, imprimi-lo:
  if (stepCount != lastStepCount) {
    Serial.print("Step count: ");
    Serial.println(stepCount);
    // Salva a contagem atual para comparação verificação     seguinte:
    lastStepCount = stepCount;
  }
}

static void eventCallback(void) {
  if (CurieIMU.stepsDetected())
    updateStepCount();
}

/* 
 Copyright (c) 2016 Intel Corporation.  Todos os direitos reservados. 

 Esta biblioteca é software livre;  você pode redistribuí-lo e / ou 
 modificá-lo sob os termos da GNU Lesser General Public 
 License conforme publicada pela Free Software Foundation;  ou 
 a versão 2.1 da Licença, ou (a seu critério) qualquer versão posterior. 

 Esta biblioteca é distribuída na esperança de que será útil, 
 mas SEM QUALQUER GARANTIA;  mesmo sem a garantia implícita de 
 COMERCIALIZAÇÃO ou ADEQUAÇÃO A UM DETERMINADO FIM.  Veja a GNU 
 Lesser General Public License para mais detalhes. 

 Você deve ter recebido uma cópia da GNU Lesser General Public 
 Licença junto com esta biblioteca;  se não, escreva para a Free Software 
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 EUA 
*/

