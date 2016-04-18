/*flav
 *Programa para enviar y recibir  
 *enviar fijaciones y recibir mensaje
 */
//si llega ' ' es que le tengo que mandar un dato nuevo

import processing.serial.*;

Serial myPort;      // The serial port
int whichKey = -1;  // Variable to hold keystoke values
int inByte = -1;    // Incoming serial data
char ardui = 0;
int numero = 1984;
float m1 = 0;
float m2 = 0;
int n1 = 0;
int n2 = 0;
int n3 = 0;
int n = 0;
boolean nuevoNumero = false;

void setup() {
  size(400, 300);
  printArray(Serial.list());
  String portName = Serial.list()[0];
  myPort = new Serial(this, portName, 9600);
}

void draw() {
  background(0);
  text("Enviado: " + whichKey, 10, 100);
  text("Recibido: " + inByte, 10, 130);
  text("Recibido char: " + ardui, 10, 160);
  text("mandó: " + n + " veces", 10, 190);

  if (nuevoNumero) {
    dividirNumeritos(numero);
    myPort.write(n1);
    myPort.write(n2);
    myPort.write(' ');
    n++;
    nuevoNumero = false;
  }
}

void serialEvent(Serial myPort) {
  inByte = myPort.read();
  if (inByte == ' '){
    nuevoNumero = true;
  }
  ardui = char(inByte);
}

void keyPressed() {
  dividirNumeritos(numero);
  myPort.write(n1);
  myPort.write(n2);
  myPort.write(' ');
  whichKey = numero;
  n++;
}

void dividirNumeritos(int n) {
  m1 = n * 0.01;
  n1 = int(m1);

  m2 = m1 - n1;
  n2 = int(m2 * 100);
  //para recomponer en arduino
  n3 = (n1 * 100) + n2;
  print("n1: " + n1 + " n2: " + n2 + " n3: " + n3);
}
