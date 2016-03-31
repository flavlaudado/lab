/*
   ACTUALIZAR TODO ESTE SKETCH PARA QUE SEA COMPATIBLE CON LOS NUEVOS
   QUE ESTÉN BIEN LAS VARIABLES, LAS FUNCIONES, ETC..
*/

//motor Z
const int pinStepsZ = 3;
const int pinDirZ = 2;
const int pinResetZ = 4;
int stepsZ = 100; //stepsZ (cambiar a mano)
//X
const int pinStepsX = 11;
const int pinDirX = 10;
const int pinResetX = 12;
//Y
const int pinStepsY = 6;
const int pinDirY = 5;
const int pinResetY = 7;

///MOTOR rollo arriba
const int pinDirUp = 30;
const int pinStepsUp = 28;
const int pinResetUp = 26;

///MOTOR rollo abajo
const int pinDirDown = 38;
const int pinStepsDown = 36;
const int pinResetDown = 34;

//variables correspondientes al motor
int speedXY = 500; //speedXY en microsegundos // speedXY //no funciona igual para ambos lados a menos de 500
int speedZ = 500; //speedZ en microsegundos // speedZ
int speedRoll = 16000;


long pasosX = 100;
long pasosY = 100;
long pasosZ = 100;
long pasosRollo = 10;

void setup() {
  Serial.begin(9600);
  pinMode(pinStepsX, OUTPUT);
  pinMode(pinDirX, OUTPUT);
  pinMode(pinResetX, OUTPUT);
  pinMode(pinStepsY, OUTPUT);
  pinMode(pinDirY, OUTPUT);
  pinMode(pinResetY, OUTPUT);
  pinMode(pinStepsZ, OUTPUT);
  pinMode(pinDirZ, OUTPUT);
  pinMode(pinResetZ, OUTPUT);
  digitalWrite(pinResetZ, HIGH);
  ///MOTOR UP
  pinMode(pinDirUp, OUTPUT);
  pinMode(pinStepsUp, OUTPUT);
  pinMode(pinResetUp, OUTPUT);

  ///MOTOR DOWN
  pinMode(pinDirDown, OUTPUT);
  pinMode(pinStepsDown, OUTPUT);
  pinMode(pinResetDown, OUTPUT);

  digitalWrite(pinResetX, HIGH);
  digitalWrite(pinResetY, HIGH);
  digitalWrite(pinResetZ, HIGH);

  /*  digitalWrite(pinResetUp, HIGH);
    digitalWrite(pinResetUp, HIGH); */
}

void loop() {

  derecha();
  abajo();
}

void moveMotor(int pinStep, int velocidad) {
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(velocidad);
}

void mueveZ() {
  adelante();
  delay(1000);
  atras();
  delay(1000);
}

void derecha() {
  digitalWrite(pinDirX, LOW);
  moveMotor(pinStepsX, speedXY);
}

void izquierda() {
  digitalWrite(pinDirX, HIGH);
  moveMotor(pinStepsX, speedXY);
}

void arriba() {
  digitalWrite(pinDirY, LOW);
  moveMotor(pinStepsY, speedXY);
}

void abajo() {
  digitalWrite(pinDirY, HIGH);
  moveMotor(pinStepsY, speedXY);
}

void atras() {
  digitalWrite(pinDirZ, LOW);
  moveMotor(pinStepsZ, speedZ);
}

void adelante() {
  digitalWrite(pinDirZ, HIGH);
  moveMotor(pinStepsZ, speedZ);
}

void rolloUpTira() {
  digitalWrite(pinResetUp, HIGH);
  digitalWrite(pinResetDown, LOW);
  digitalWrite(pinDirUp, LOW);
  for (int i = 0; i < pasosRollo; i++) {
    moveMotor(pinStepsUp, speedRoll);
  }
}

void rolloUpSuelta() {
  digitalWrite(pinResetUp, HIGH);
  digitalWrite(pinResetDown, LOW);
  digitalWrite(pinDirUp, HIGH);
  for (int i = 0; i < pasosRollo; i++) {
    moveMotor(pinStepsUp, speedRoll);
  }
}

void rolloDownTira() {
  digitalWrite(pinResetDown, HIGH);
  digitalWrite(pinResetUp, LOW);
  digitalWrite(pinDirDown, LOW);
  for (int i = 0; i < pasosRollo; i++) {
    moveMotor(pinStepsDown, speedRoll);
  }
}

void rolloDownSuelta() {
  digitalWrite(pinResetDown, HIGH);
  digitalWrite(pinResetUp, LOW);
  digitalWrite(pinDirUp, HIGH);
  for (int i = 0; i < pasosRollo; i++) {
    moveMotor(pinStepsDown, speedRoll);
  }
}



