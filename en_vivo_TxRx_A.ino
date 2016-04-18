/*
   programa test para ir mandando y recibiendo datos por puerto serial
   recibiendo dato, marcar y pedir nuevo dato
   seguir!!
     reemplazar arrayRead()
     searialRead(): acá voy a fijarme en el si está completo el nuevo dato
     y lo guardo en un int y le aplico el factor
     mirar p5 examples/librarys/serial/SimpleWrite
*/

String inputString = "";// data que entra
String copia = "";
boolean stringComplete = false;  // whether the string is complete
int newPos = 0;
int pixelX[726];
int n = 0;
int input = 0;

//leds testigos para usos múltiples
const int pinLed1 = 41;
const int pinLed2 = 40;
int led1;
int led2;
boolean flag = true;
boolean escribir = false;
boolean enviar = false;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  pinMode(9, INPUT);
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
}

void loop() {
  if (stringComplete) {//aca guardo la posición
    newPos = inputString.toInt();//función para convertir String en int
    copia = inputString;
    //pixelX[n] = newPos;
    //n++;
    //Serial.println(newPos);
    Serial.write(newPos);//me comunico con el otro programa
    inputString = "";//limpio el string
    stringComplete = false;
    //marcar posicion en la maquina
  }
  if (digitalRead(9) == HIGH and flag == true){
    flag = false;
    escribir = true;
  }

  if (digitalRead(9) == LOW  and flag == false){
    flag = true;
  }  
  if (escribir) {//esto me indica que estoy interpretando bien el dato q entra
    Serial.println(newPos);//ecribe el caracter, el numero que tengo en codigo ascii
    for (int i = 0; i < newPos; i++) {
    digitalWrite(pinLed1, HIGH);
    delay(700);
    digitalWrite(pinLed1, LOW);
    delay(700);
    enviar = true;
    }
    escribir = false;
  }
  if (enviar){
    Serial.write(' ');
    enviar = false;
  }
}

void serialEvent() {//cuando entra data la guardo en una variable de tipo String
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == ' ') {
      stringComplete = true;
    }
  }
}

/*
  String inputString = "",
  boolean stringComplete = false;

  void setup() {
  Serial.begin(9600);
  inputString.reserve(200);

  }

  void loop() {
  if (stringComplete){
    Serial.println(inputString);
    inputString = "";
    stringComplete = false;
  }
  }

  void serialEvent(){
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += inChar;
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
  } */

