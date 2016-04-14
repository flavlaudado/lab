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
}

void serialEvent(Serial myPort) {
  inByte = myPort.read();
 ardui = char(inByte);
}

void keyPressed() {
  // Send the keystroke out:
  myPort.write(key);
  whichKey = key;
}