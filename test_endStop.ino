/*
 * Programa test de fines de carrera magnéticos, sensor hall effect
 */
//X
const int pinStepsX = 11;
const int pinDirX = 10;
const int pinResetX = 12;
//Y
const int pinStepsY = 6;
const int pinDirY = 5;
const int pinResetY = 7;
//motor Z
const int pinStepsZ = 3;
const int pinDirZ = 2;
const int pinResetZ = 4;

int speedXY = 500; 
int speedZ = 500; 

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

  digitalWrite(pinResetX, HIGH);
  digitalWrite(pinResetY, HIGH);
  //digitalWrite(pinResetZ, HIGH);
}

void loop() {
  //Serial.println(analogRead(A0));
//probando eje X
  if (analogRead(A0) < 10) {
    for(int i = 0; i <700; i++){
      derecha();
    }
  }
  izquierda();

//probando eje Y
/*  if (analogRead(A1) < 10) {
    for(int i = 0; i <700; i++){
      abajo();
    }
  }
  arriba();
}
*/
}

void arriba() {
  digitalWrite(pinDirY, LOW);
  moveMotor(pinStepsY, speedXY);
}

void abajo() {
  digitalWrite(pinDirY, HIGH);
  moveMotor(pinStepsY, speedXY);
}

void derecha() {
  digitalWrite(pinDirX, LOW);
  moveMotor(pinStepsX, speedXY);
}

void izquierda() {
  digitalWrite(pinDirX, HIGH);
  moveMotor(pinStepsX, speedXY);
}

void moveMotor(int pinStep, int velocidad) {
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(velocidad);
}
