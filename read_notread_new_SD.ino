/*
   Flavia Laudado.
   Software de control de dispositivo mecatronico desarrollado para reproducir la mirada sobre un texto,
   quemando en posiciones específicas.
*/

//incluimos las dos librerías necesarias para trabajar con SD
// FORMATEAR TARJETA SD EN FORMATO FAT 32
#include <SPI.h>
#include <SD.h>

//variables para utilizar la memoria SD
File myFileX, myFileY, punX, punY;//archivos de texto
unsigned long punteroX = 0;
unsigned long punteroY = 0;
boolean flag_posAntX = true;
boolean flag_posAntY = true;
int r = 0;
unsigned long puntero = 0;

int burningTime = 1000;


/*
//#include <avr/pgmspace.h>

  const PROGMEM uint16_t pixelX[] = { 1000, 800, 500, 350, 100, 500, 900, 50};
  const PROGMEM uint16_t pixelY[] = { 0, 150, 500, 600, 100, 300, 700, 500};
*/
/* //array con fijaciones fuera de los límites
  const PROGMEM uint16_t pixelX[] = {  1000, 950, 700, 600, 550, 1100, 500, 200, 600};
  const PROGMEM uint16_t pixelY[] = {  300, 400, 450, 50, 500, 400, 600, 500, 450};
*/

long arraySize = 19;//726; //8; //cantidad de fijaciones
long n = 1; //actuall point in array read
long m = 0; //before point in array read or 'n' data value

//configurar estas variables según dimensiones de hoja a usar, valores en pixeles
// OJO, SON LOS LÍMITES DE LAS POSICIONES
const int minX = 0;
const int maxX = 1900;
const int minY = 0;
const int maxY = 1000;

//variables correspondientes al motor
const int speedXY = 500; //speedXY en microsegundos // speedXY //no funciona igual para ambos lados a menos de 500
const int speedZ = 500; //speedZ en microsegundos // speedZ

const int speedXY_findZero = 250;

//PINES DE CONEXIÓN DE LOS MOTORES
//motor Z
const int pinStepsZ = 3;
const int pinDirZ = 2;
const int pinResetZ = 4;

const int stepsZ = 80; //stepsZ (cambiar a mano)
//X
const int pinStepsX = 11;
const int pinDirX = 10;
const int pinResetX = 12;
//Y
const int pinStepsY = 6;
const int pinDirY = 5;
const int pinResetY = 7;

int flag = LOW;

//finales de carrera
const int endStopX = A0;
const int thresholdEndStopX = 75;
int valEndX;
int flagEndX = LOW;

const int endStopY = A1;
const int thresholdEndStopY = 75;
int valEndY;
int flagEndY = LOW;

const int endStopZ = A2;
const int umbralEndStopZ = 75;
int valEndZ;
int flagEndZ = LOW;

boolean moverX = false;
boolean moverY = false;

long counterX = 0;
long counterY = 0;

/*factor de conversión de pixel a pasos
    1000 pasos son 6,2 mm(de motor paso a paso de brida 28mm con acople de 5mm a 8mm y
  varilla roscada de 8mm)
  como convertir pixeles a pasos:
  (159mm(ancho de formato de texto)* 1000pap/ 6.2mm)/ 1890pX(ancho en pixeles) = f
  (159mm(ancho de formato de texto)* 1000pap/ 6.2mm)= 25645,16 (cantidad de pasos necesarios para recorrer el ancho del formato del texto)
  25646,16 / 1890pX= 13.56 = f */
float f = 5;//con guias lineales 13.5

long posX = 0; //Pasos convertidos a partir de la variable en X
long posY = 0; //Pasos convertidos a partir de la variable en Y
long posXpasos = 0;
long posYpasos = 0;
long posAntX = 0; //PosX del anterior loop
long posAntY = 0; //PosY del anterior loop

boolean flagTemperature = false;// flagTemperature
int temperatureSensor = 0;
const int temperaturePin = 44;
int temperatureLoopCounter = 4; //arranca solo si está en 4 temperatureLoopCounter
const int minCounterTemperature = 3;

int flagFindZero = HIGH;//si pongo LOW evita buscar el cero
int flagEnableMotors = HIGH;

//leds testigos para usos múltiples
const int pinLed1 = 41;
const int pinLed2 = 40;
int led1;
int led2;

/*
  //MOTOR rollo arriba
  const int pinDirUp = 30;
  const int pinStepsUp = 28;
  const int pinResetUp = 26;

  //MOTOR rollo abajo
  const int pinDirDown = 38;
  const int pinStepsDown = 36;
  const int pinResetDown = 34;

  int speedRoll = 16000;
  //sensor para marca de posición de rollo
  int POTE;
  int LDR;
  int LED = 13;

  //VARIABLES SENSOR LDR
  boolean readSheet = true; //readSheet
  boolean flagEnableRollMotor = false;//flagEnableRollMotor
  boolean exitOfMark = true;// exitOfMark

*/

void setup() {
  //Serial.begin(9600);//115200);

  pinMode(pinStepsX, OUTPUT);
  pinMode(pinDirX, OUTPUT);
  pinMode(pinResetX, OUTPUT);

  pinMode(pinStepsY, OUTPUT);
  pinMode(pinDirY, OUTPUT);
  pinMode(pinResetY, OUTPUT);

  pinMode(pinStepsZ, OUTPUT);
  pinMode(pinDirZ, OUTPUT);
  pinMode(pinResetZ, OUTPUT);

  digitalWrite(pinResetX, LOW);
  digitalWrite(pinResetY, LOW);
  //digitalWrite(pinResetZ, HIGH);

  //SENSORES
  //  pinMode(LED, OUTPUT);
  pinMode(temperaturePin, INPUT);

  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);

  //sequenceUp_automatique();//dami este es para probar el sensor
  delay(3000); //para que no arranque directo
  /*
      ///MOTOR UP
      pinMode(pinDirUp, OUTPUT);
      pinMode(pinStepsUp, OUTPUT);
      pinMode(pinResetUp, OUTPUT);

      ///MOTOR DOWN
      pinMode(pinDirDown, OUTPUT);
      pinMode(pinStepsDown, OUTPUT);
      pinMode(pinResetDown, OUTPUT);

      digitalWrite(pinStepsUp, LOW);
      digitalWrite(pinResetDown, LOW);
      digitalWrite(pinResetDown, LOW);
  */

  //memoria SD
  Serial.begin(9600);
  Serial.println("Inicializando SD...");

  if (SD.begin()) { //esto aprueba que la memoria SD está disponible
    Serial.println("OK...");
    setPuntero();
    //getPunteroX();
    //getPunteroY();
  }
  else {
    Serial.println("No encuentra archivo");
    //sequenceDown();
  }
}

void loop() {
  //Esperar que la resistencia caliente
  counterTemperatureLoops(); // put 3 in:  "int temperatureLoopCounter = 3;" to start the machine automatically

  // BUSCAR EL (0,0)
  if (flagFindZero == HIGH) {
    findZero();
  }
  //a partir de acá la maquina está lista para Burn
  if ((temperatureLoopCounter > minCounterTemperature) && (flagFindZero == LOW)) {
    burn();
  }
}

void counterTemperatureLoops() {  //secuencia para contar ciclos de prendido y apagado de la resistencia de quemado
  temperatureSensor = digitalRead(temperaturePin);

  if (temperatureSensor == LOW && flagTemperature == false ) {
    temperatureLoopCounter++;
    flagTemperature = true;
  }
  if (temperatureSensor == HIGH && flagTemperature == true ) {
    flagTemperature = false;
  }
}

void findZero() {
  enableMotorsXY(); //Prendo motores para buscar el cero
  digitalWrite(pinDirX, HIGH);
  digitalWrite(pinDirY, LOW);
  //fin de carrera en X
  if (flagEndX == LOW) {
    valEndX = analogRead(endStopX);
    if ((valEndX > thresholdEndStopX) && (flagEndX == LOW)) {
      moverX = true;
    }
    if (valEndX < thresholdEndStopX) {
      flagEndX = HIGH;
      digitalWrite(pinResetX, LOW); //apago motorX
      moverX = false;
    }
  }
  //fin de carrera en Y
  if (flagEndY == LOW) {
    valEndY = analogRead(endStopY); //leo fin de carrera en Y
    if ((valEndY > thresholdEndStopY) && (flagEndY == LOW)) {
      //moveMotors(pinStepsY, speedXY);
      moverY = true;
    }
    if (valEndY < thresholdEndStopY) {
      flagEndY = HIGH;
      digitalWrite(pinResetY, LOW);
      moverY = false;
    }
  }
  if ((moverX == true) && (moverY == true)) { //para mover los 2 motores juntos
    moveMotorXY();
  } else {//sino se mueven por separados
    if (moverX = true) {
      moveMotors(pinStepsX, speedXY_findZero);
    }
    if (moverY = true) {
      moveMotors(pinStepsY, speedXY_findZero);
    }
  }
  if (flagEndX == HIGH && flagEndY == HIGH) { //si tocaron ambos fines de carrera ya está en 0,0
    flagFindZero = LOW;
    flag = LOW;//bug
    delay(50);
  }
}

void burn() {
  if (flag == LOW) {//solo se ejecuta la primera vez
    arrayReadSD();
    // digitalWrite prepara los motores para mover
    //secuencia de encendido()
    digitalWrite(pinResetX, HIGH);
    digitalWrite(pinResetY, HIGH);
    flag = HIGH;
    //    Serial.println("ENCENDIDO");
  }/*
        if ( readSheet == true) { //empieza a Burn
          //apagar motores de rollo una vez
          if (flagEnableRollMotor == false) {
            digitalWrite(pinResetUp, LOW);
            digitalWrite(pinResetDown, LOW);
            flagEnableRollMotor = true;
          } */
  //movimiento de motores en X e Y
  if (flag == HIGH) {//primero setear la posición y luego moverlos
    if (posXpasos > 0) {//hacia la izquierda
      digitalWrite(pinDirX, HIGH);//HIGH);
    }
    else if (posXpasos < 0) {
      digitalWrite(pinDirX, LOW);//LOW);
    }
    if (posYpasos > 0) {//hacia abajo
      digitalWrite(pinDirY, HIGH);
    }
    else if (posYpasos < 0) {//hacia arriba
      digitalWrite(pinDirY, LOW);
    }

    if ((counterX != abs(posXpasos)) && (counterY != abs(posYpasos))) {
      moveMotorXY();
      counterX++;
      counterY++;
    } else {
      if (counterX != abs(posXpasos)) {
        moveMotors(pinStepsX, speedXY);
        counterX++;
      }
      if (counterY != abs(posYpasos)) {
        moveMotors(pinStepsY, speedXY);
        counterY++;
      }
    }
  }
  /*
    if (readSheet == false) {//si no esta leyendo, ir a nueva pagina
    sheetSensing();//Sensar hoja, para saber si esta en una marca o no
    } */
  if (counterX == abs(posXpasos) && counterY == abs(posYpasos)) {
    //sequenceDown();//marco la fijacion
    delay(500);
    counterX = 0;
    counterY = 0;
    arrayReadSD(); //busca una nueva posición
  }
}

void enableMotorsXY() {
  if ((flagFindZero == HIGH) && (flagEnableMotors == HIGH)) {
    digitalWrite(pinResetX, HIGH);
    digitalWrite(pinResetY, HIGH);
    flagEnableMotors = LOW;
  }
}

void moveMotors(int pinStep, int velocidad) {
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(velocidad);
}

void moveMotorXY() {
  digitalWrite(pinStepsX, HIGH);
  digitalWrite(pinStepsY, HIGH);
  delayMicroseconds(speedXY);
  digitalWrite(pinStepsX, LOW);
  digitalWrite(pinStepsY, LOW);
  delayMicroseconds(speedXY);
}

void sequenceDown() {
  turnOffXY();
  digitalWrite(pinDirZ, HIGH);
  for (int i = 0; i < stepsZ; i++) {
    moveMotors(pinStepsZ, speedZ);
  }
  delay(burningTime);
  flagEndZ = LOW;
  sequenceUp_automatique();
  //sequenceUp_step_fixed();
  turnOnXY();
}
void sequenceUp_automatique() {//función para levantar en Z, con sensor
  digitalWrite(pinDirZ, LOW);
  while (flagEndZ == LOW) {
    valEndZ = analogRead(endStopZ);
    if (valEndZ > umbralEndStopZ) {
      moveMotors(pinStepsZ, speedZ);
    } else 
      flagEndZ = HIGH; //flag en HIGH cuando está en 0
    }
  }
}

void sequenceUp_step_fixed() { //función antigüa, sin sensor de Z
  digitalWrite(pinDirZ, LOW);
  for (int i = 0; i < stepsZ; i++) {
    moveMotors(pinStepsZ, speedZ);
  }
}

void turnOffXY() {
  digitalWrite(pinResetX, LOW);
  digitalWrite(pinResetY, LOW);
}

void turnOnXY() {
  digitalWrite(pinResetX, HIGH);
  digitalWrite(pinResetY, HIGH);
}

void setPuntero() { //cada vez que arranca se fija en cuanto quedó el puntero de cada archivo
  punX = SD.open("punteroX.txt", FILE_WRITE);
  punX.seek(0);//me posiciono en el inicio del archivo
  punX.print(punteroX);//escribe la nueva posicion del puntero
  Serial.print("Escribo punteros punteroX: ");
  Serial.print(punteroX);
  punX.close();

  punY = SD.open("punteroY.txt", FILE_WRITE);
  punY.seek(0);//me posiciono en el inicio del archivo
  punY.print(punteroY);//escribe la nueva posicion del puntero
  Serial.print(", punteroY: ");
  Serial.println(punteroY);
  punY.close();//guarda y cierra el archivo
}

void getPunteroX() {//obtengo el lugar del punteroX
  punX = SD.open("punteroX.txt", FILE_READ);//abro el archivo
  punX.seek(0);//me posiciono en el inicio
  punteroX = punX.parseInt();//agarro la primer posicion
  Serial.print(" get punteroX: ");
  Serial.print(punteroX);
  punX.close();//cierro el archivo
}

void getPunteroY() {//obtengo el lugar del punteroY
  punY = SD.open("punteroY.txt", FILE_READ);//abro el archivo
  punY.seek(0);//me posiciono en el inicio
  punteroY = punY.parseInt();//agarro la primer posicion
  Serial.print(" get punteroY: ");
  Serial.print(punteroY);
  punY.close();//cierro el archivo
}

void arrayReadSD() {//obtengo posiciones de la tarjeta SD
  Serial.println("Entrando a arrayReadSD()");
  //solo hago getPuntero() si se cortó la luz en el setup()
  myFileX = SD.open("x1.txt", FILE_READ);//abro el archivo de fijaciones en X
  myFileX.seek(punteroX);//posiciono el puntero
  if (myFileX.available() > 0) {//me fijo si todavía hay datos para leer
    Serial.print(" Entrando al archivo X");
    if (flag_posAntX) { //si es la primera, agarro la primera como anterior
      myFileX.seek(0);
      posAntX = myFileX.parseInt();//agarro la posicion inicial, para hacer el calculo
      flag_posAntX = false;//flag para hacerlo solo la primera vez
    }
    posX = myFileX.parseInt(); //separa los numeros y lo guarda en posX
    punteroX = myFileX.position(); //agarra la posicion actual
    myFileX.close();
    Serial.print(" punteroX: ");
    Serial.print(punteroX);
    Serial.print(", valAntX: ");
    Serial.print(posAntX);
    Serial.print(", valX: ");
    Serial.println(posX);

  } else { //si terminó de leer el archivo
    Serial.println("termino el archivo");
    punteroX = 0;//me posiciono de vuelta en 0
    myFileX.close();//guardo y cierro
    //aca terminó de leer el txt, o sea que tiene que buscar cero y quemar otra hoja
    punteroX = 0;
    punteroY = 0;
    flag_posAntX = true;
    flag_posAntY = true;
    temperatureLoopCounter = minCounterTemperature + 1;//modificado para que arranque solo
    flagFindZero = HIGH;
    flagEndX = LOW;
    flagEndY = LOW;
    moverX = false;
    moverY = false;
  }

  posXpasos = (posX - posAntX) * f;//variable con la cantidad de pasos de motor
  posAntX = posX; //actualizo el valor anterior

  //getPunteroY();//obtengo la ultima posicion del punteroY
  myFileY = SD.open("y1.txt", FILE_READ);//abro el archivo de fijaciones en Y
  myFileY.seek(punteroY);//posiciono el puntero
  if (myFileY.available() > 0) {
    Serial.print(" Entrando al archivo Y");
    if (flag_posAntY) {//si es la primera, agarro la primera como anterior
      myFileY.seek(0);
      posAntY = myFileY.parseInt();//agarro la posicion inicial, para hacer el calculo
      flag_posAntY = false;//flag para hacerlo solo la primera vez
    }
    posY = myFileY.parseInt(); //separa los numeros y lo guarda en posY
    punteroY = myFileY.position(); //agarra la posicion actual
    myFileY.close();//guardo y cierro
    Serial.print(" punteroY: ");
    Serial.print(punteroY);
    Serial.print(", valAntY: ");
    Serial.print(posAntY);
    Serial.print(", valY: ");
    Serial.println(posY);
  } else {
    Serial.println("termino el archivo");
    punteroY = 0;//me posiciono de vuelta en 0
    myFileY.close();//guardo y cierro
    flag_posAntY = true;
    //aca terminó de leer el txt, o sea que tiene que buscar cero y quemar otra hoja
    punteroX = 0;
    punteroY = 0;
    flag_posAntX = true;
    flag_posAntY = true;
    temperatureLoopCounter = minCounterTemperature + 1;//modificado para que arranque solo
    flagFindZero = HIGH;
    flagEndX = LOW;
    flagEndY = LOW;
    moverX = false;
    moverY = false;
  }
  posYpasos = (posY - posAntY) * f;//variable con la cantidad de pasos de motor
  posAntY = posY;//actualizo el valor anterior
  
  /*//Secuencia para que cada X fijaciones guarde su posición
    r++;
    if (r > 2) { //guardo el puntero cada X fijaciones
    setPuntero();//actualizo los punteros
    r = 0;
    } */
}

/*
  void arrayRead() {

  //   chequear antes de moverme si se puede ir o no a ese punto, segun límites de ancho de hoja
  //   si está fuera de los límites paso al siguiente punto (sin actualizar el punto anterior)
  //   tengo que saber mi posición actual Y hacer el calculo Y ver si está dentro de mi hoja
  //   si no está dentro de mi hoja n++

  posX = pgm_read_word_near(pixelX + n);//leo nueva cordenada en X en pixeles
  while ( posX < minX || posX > maxX) {//si posX se sale de lo límites
    n++;                               //avanzo una posición
    posX = pgm_read_word_near(pixelX + n);
    //    digitalWrite(pinLed1, HIGH);
    //    delay(200);
    //    digitalWrite(pinLed1, LOW);
  }

  posY = pgm_read_word_near(pixelY + n);//leo nueva cordenada en Y en pixeles
  while ( posY < minY || posY > maxY) {//si posY se sale de lo límites
    n++;                               //avanzo una posición
    posY = pgm_read_word_near(pixelY + n);
    //    digitalWrite(pinLed2, HIGH);
    //    delay(500);
    //    digitalWrite(pinLed2, LOW);
  }
  posY = pgm_read_word_near(pixelY + n);//leo nueva posición en Y
  posX = pgm_read_word_near(pixelX + n);//leo nueva posición en X

  posX = (posX - pgm_read_word_near(pixelX + m)) * f; //posX = cantidad de pasos de motor en "x" que debe efectuar para ir a destino
  posY = (posY - pgm_read_word_near(pixelY + m)) * f; //posY = cantidad de pasos de motor en "y" que debe efectuar para ir a destino

  }
*/

/*
  void sheetSensing() {
  //me fijo si el LDR detecta la marca
  if (exitOfMark == true) {
    digitalWrite(pinResetUp, HIGH);
    for (int i = 0; i < 50; i++) {
      moveMotors(pinStepsUp, speedRoll);
    }
    exitOfMark = false;
  }
  POTE = analogRead(A4); //usado para calibración
  LDR = analogRead(A7);
  if (flagEnableRollMotor == true) {
    digitalWrite(pinResetUp, HIGH);
    digitalWrite(pinDirUp, LOW);
    flagEnableRollMotor = false;
  }
  moveMotors(pinStepsUp, speedRoll);
  if (LDR > POTE) { //si detecta marca, haY que leer nueva hoja
    digitalWrite(LED, HIGH);
    readSheet = true;
  }
  else {
    digitalWrite(LED, LOW);
  }
  } */
