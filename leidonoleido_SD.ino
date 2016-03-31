//incluimos las dos librerías necesarias para trabajar con SD
#include <SPI.h>
#include <SD.h>


//incluimos la libreria PROGMEM para poder guardar mas datos en la memoria de programa
//ya que los datos de fijaciones son muchisimos
#include <avr/pgmspace.h>

//PROGMEM prog_int16_t pixelX[]=
const PROGMEM uint16_t pixelX[] = {1900, 1281, 1276, 1078, 1103, 1805, 1827, 1686, 1654, 1645, 1496, 1507, 1185, 1260, 986, 1005, 890, 839, 758, 778, 512, 395, 377, 285, 288, 121, 126, 1842, 1845, 1703, 1715, 1379, 1294, 1272, 1125, 1024, 933, 762, 1024, 424, 442, 230, 220, 15, 41, 1838, 1685, 1726, 1507, 1538, 1393, 1410, 1328, 1342, 1158, 1169, 1158, 958, 963, 919, 935, 710, 730, 616, 650, 493, 523, 404, 411, 236, 243, 191, 197, 7, 1881, 1837, 1635, 1653, 1443, 1398, 1290, 1242, 1171, 1172, 1069, 1074, 880, 882, 793, 795, 608, 615, 460, 456, 364, 322, 91, 77, 1848, 1839, 1767, 1765, 1677, 1661, 1496, 1493, 1309, 1306, 1236, 1249, 1178, 1186, 987, 985, 909, 916, 732, 735, 609, 607, 377, 377, 191, 211, 1819, 1887, 1707, 1709, 1488, 1487, 1438, 1443, 1369, 1370, 1178, 1192, 895, 927, 682, 699, 642, 603, 596, 494, 341, 327, 314, 224, 125, 118, 1823, 1834, 1783, 1801, 1709, 1517, 1528, 1440, 1458, 1159, 1033, 1031, 870, 872, 829, 823, 641, 654, 546, 562, 303, 377, 176, 175, 38, 47, 1762, 1776, 1649, 1646, 1410, 1425, 1337, 1339, 1830, 1814, 1703, 1703, 1600, 1592, 1428, 1423, 1209, 1212, 1209, 1212, 1192, 1212, 1192, 1212, 880, 861, 880, 861, 739, 735, 580, 584, 404, 406, 404, 406, 217, 242, 217, 242, 1805, 1797, 1805, 1797, 1611, 1594, 1418, 1414, 1298, 1295, 890, 915, 706, 709, 485, 481, 399, 405, 244, 251, 201, 198, 1755, 1772, 1648, 1649, 1596, 1582, 1396, 1393, 1333, 1324, 1196, 1205, 1014, 1023, 794, 799, 651, 670, 454, 473, 171, 170, 11, 12, 1884, 1884, 1667, 1677, 1544, 1539, 1342, 1267, 1267, 994, 995, 795, 819, 679, 671, 430, 428, 280, 274, 195, 192, 43, 60, 1846, 1854, 1669, 1634, 1500, 1522, 1283, 1243, 1231, 1211, 1132, 1146, 953, 962, 912, 907, 674, 677, 607, 615, 365, 371, 182, 192, 1802, 1825, 1589, 1569, 1551, 1360, 1404, 1293, 1100, 1129, 977, 998, 918, 922, 847, 869, 651, 666, 588, 596, 467, 486, 370, 380, 292, 330, 130, 12, 21, 1803, 1802, 1562, 1580, 1509, 1512, 1413, 1433, 1243, 1263, 1098, 1056, 1049, 924, 820, 831, 547, 549, 406, 419, 314, 324, 196, 205, 9, 1858, 1598, 1608, 1479, 1475, 1415, 1420, 1247, 1217, 1210, 1011, 1014, 845, 862, 666, 829, 516, 519, 306, 308, 94, 87, 1817, 1793, 1580, 1566, 1399, 1386, 1361, 1350, 1197, 1184, 1052, 1005, 993, 705, 673, 474, 347, 348, 168, 106, 153, 1825, 1768, 1816, 1564, 1550, 1338, 1235, 1067, 1072, 947, 933, 870, 868, 829, 828, 640, 611, 417, 399, 247, 247, 1784, 1792, 1658, 1681, 1534, 1530, 1461, 1446, 1391, 1079, 1089, 1021, 805, 796, 651, 679, 486, 498, 305, 255, 265, 15, 1884, 1883, 1652, 1649, 1501, 1507, 1312, 1294, 1052, 1058, 887, 921, 813, 853, 686, 570, 587, 300, 311, 98, 99, 38, 56, 1860, 1887, 1693, 1719, 1573, 1576, 1326, 1322, 1236, 1326, 956, 966, 899, 918, 785, 809, 526, 536, 279, 296, 159, 187, 64, 51, 1896, 1900, 1720, 1711, 1665, 1671, 1455, 1458, 1414, 1400, 1218, 1217, 1158, 1146, 1026, 1018, 995, 988, 845, 848, 623, 623, 532, 424, 432, 226, 258, 115, 115, 1851, 1869, 1616, 1628, 1550, 1481, 1467, 1361, 1373, 1140, 1157, 968, 964, 731, 725, 663, 665, 1800, 1823, 1617, 1594, 1347, 1355, 1127, 1065, 1084, 825, 845, 628, 588, 595, 382, 391, 335, 326, 173, 177, 1873, 1863, 1843, 1772, 1745, 1651, 1669, 1577, 1592, 1418, 1449, 1211, 1221, 926, 938, 852, 803, 822, 586, 585, 488, 482, 330, 324, 183, 196, 11, 44, 1882, 1860, 1834, 1792, 1834, 1610, 1627, 1400, 1394, 1184, 1188, 1060, 1068, 774, 786, 576, 589, 486, 527, 287, 281, 107, 106, 1847, 1850, 1621, 1625, 1483, 1439, 1411, 1262, 1241, 1116, 1094, 945, 941, 761, 758, 547, 546, 470, 459, 419, 422, 347, 337, 196, 201, 1848, 1855, 1635, 1623, 1564, 1557, 1285, 1265, 1099, 1071, 952, 961, 745, 745, 557, 561, 345, 345, 121, 119, 1828, 1769, 1662, 1543, 1565, 1350, 1359, 1177, 1189, 1033, 1024, 910, 924, 810, 806, 646, 634, 518, 516, 414, 415, 211, 209, 166, 1812, 1803, 1730, 1725, 1522, 1555, 1325, 1323, 1104, 1104, 956, 942, 840, 836, 583, 590, 338, 214, 235, 109, 114, 1803, 1810, 1650, 1663, 1407, 1440, 1241, 1263, 1041, 1038, 914, 927, 795, 806, 671, 685, 401, 414, 299, 272, 23, 38, 1900};
//PROGMEM prog_int16_t pixelY[]=
const PROGMEM uint16_t pixelY[] = {0, 0, 1, 2, 0, 201, 165, 176, 173, 186, 167, 181, 180, 181, 178, 187, 164, 186, 180, 168, 171, 239, 168, 239, 187, 165, 173, 317, 231, 256, 262, 224, 301, 246, 244, 304, 303, 241, 304, 228, 225, 244, 240, 241, 258, 290, 289, 307, 321, 317, 292, 315, 301, 306, 302, 328, 302, 302, 329, 303, 325, 296, 315, 294, 297, 309, 308, 304, 304, 292, 318, 312, 329, 308, 359, 374, 353, 371, 385, 373, 397, 361, 376, 380, 373, 363, 390, 376, 379, 368, 373, 376, 358, 373, 377, 364, 353, 381, 426, 444, 441, 468, 413, 462, 437, 481, 441, 460, 426, 434, 457, 451, 458, 473, 433, 422, 453, 436, 434, 418, 405, 420, 425, 436, 516, 462, 471, 471, 470, 488, 506, 525, 480, 496, 478, 495, 495, 477, 505, 513, 500, 503, 485, 504, 464, 498, 487, 468, 471, 491, 544, 561, 564, 559, 545, 562, 565, 534, 533, 544, 546, 535, 527, 548, 525, 540, 524, 543, 524, 536, 524, 548, 542, 570, 533, 556, 595, 626, 612, 627, 604, 608, 613, 632, 667, 692, 668, 670, 645, 678, 662, 680, 674, 683, 674, 683, 679, 683, 679, 683, 675, 701, 675, 701, 659, 677, 677, 678, 654, 673, 654, 673, 665, 683, 665, 683, 732, 747, 732, 747, 730, 754, 722, 721, 736, 742, 780, 785, 728, 756, 729, 757, 752, 755, 735, 727, 763, 752, 828, 815, 805, 817, 815, 832, 809, 814, 807, 816, 789, 795, 791, 784, 798, 811, 804, 793, 780, 772, 789, 802, 806, 790, 825, 821, 883, 863, 854, 858, 857, 851, 869, 881, 880, 840, 854, 854, 864, 842, 838, 871, 830, 836, 847, 857, 877, 914, 925, 920, 911, 934, 928, 921, 929, 925, 932, 923, 922, 917, 915, 925, 925, 914, 931, 924, 927, 927, 920, 936, 957, 980, 999, 982, 998, 990, 985, 985, 993, 1007, 969, 972, 987, 972, 976, 964, 966, 975, 967, 985, 978, 977, 978, 980, 994, 989, 966, 1008, 970, 997, 1015, 1030, 1029, 1056, 1003, 1027, 1034, 1010, 1042, 1047, 1055, 1071, 1029, 1029, 1045, 1056, 1013, 1040, 1042, 1053, 1033, 1057, 1018, 1027, 1043, 1082, 1107, 1118, 1086, 1119, 1094, 1112, 1099, 1120, 1090, 1114, 1130, 1093, 1087, 1081, 1109, 1114, 1122, 1099, 1103, 1094, 1117, 1149, 1176, 1144, 1158, 1141, 1156, 1142, 1144, 1168, 1173, 1151, 1163, 1122, 1151, 1149, 1150, 1180, 1160, 1154, 1151, 1167, 1199, 1200, 1219, 1196, 1219, 1207, 1223, 1216, 1218, 1216, 1232, 1202, 1220, 1213, 1204, 1197, 1211, 1210, 1228, 1214, 1217, 1351, 1366, 1333, 1335, 1353, 1343, 1331, 1337, 1342, 1353, 1347, 1334, 1370, 1370, 1356, 1336, 1336, 1349, 1302, 1342, 1366, 1364, 1409, 1411, 1417, 1431, 1408, 1404, 1387, 1405, 1382, 1407, 1397, 1419, 1377, 1423, 1381, 1416, 1416, 1398, 1396, 1398, 1416, 1397, 1395, 1425, 1474, 1469, 1452, 1463, 1472, 1443, 1460, 1451, 1443, 1454, 1458, 1446, 1450, 1450, 1459, 1470, 1477, 1492, 1495, 1487, 1473, 1452, 1499, 1517, 1543, 1510, 1545, 1527, 1517, 1542, 1522, 1520, 1543, 1539, 1533, 1565, 1552, 1537, 1541, 1534, 1543, 1525, 1530, 1514, 1529, 1537, 1524, 1511, 1552, 1518, 1536, 1537, 1593, 1573, 1586, 1562, 1566, 1543, 1593, 1626, 1605, 1617, 1596, 1584, 1578, 1588, 1576, 1602, 1600, 1659, 1664, 1645, 1630, 1636, 1633, 1654, 1638, 1642, 1631, 1652, 1624, 1619, 1646, 1630, 1647, 1633, 1667, 1626, 1641, 1676, 1737, 1687, 1722, 1687, 1727, 1729, 1708, 1715, 1690, 1697, 1678, 1697, 1685, 1712, 1684, 1684, 1705, 1721, 1717, 1724, 1715, 1681, 1726, 1704, 1716, 1710, 1715, 1751, 1791, 1736, 1792, 1736, 1781, 1802, 1768, 1790, 1746, 1765, 1756, 1771, 1770, 1774, 1777, 1796, 1762, 1758, 1739, 1741, 1733, 1756, 1791, 1819, 1812, 1839, 1854, 1805, 1844, 1816, 1832, 1835, 1855, 1829, 1846, 1814, 1821, 1850, 1836, 1841, 1845, 1828, 1813, 1815, 1827, 1826, 1813, 1899, 1862, 1919, 1902, 1912, 1906, 1885, 1870, 1858, 1871, 1863, 1868, 1908, 1889, 1907, 1869, 1894, 1876, 1903, 1876, 1926, 1939, 1926, 1977, 1969, 1963, 1945, 1934, 1922, 1928, 1944, 1926, 1946, 1912, 1918, 1939, 1919, 1967, 1931, 1951, 1943, 1952, 1947, 1918, 2008, 1989, 2004, 1979, 1987, 2003, 1993, 2008, 2010, 2005, 2004, 2023, 1994, 1990, 2022, 2000, 1987, 2018, 2019, 1999, 2021, 2048, 2076, 2067, 2068, 2066, 2064, 2069, 2085, 2052, 2074, 2052, 2068, 2043, 2063, 2058, 2068, 2055, 2077, 2096, 2066, 2081, 2086, 0};

/*
  const PROGMEM uint16_t pixelX[] = {  1900, 50, 0};
  const PROGMEM uint16_t pixelY[] = {  0, 50, 0};
*/
/*
  PROGMEM prog_int16_t pixelX[]= {  1000, 900, 500, 1000, 800, 300, 500, 1000};
  PROGMEM prog_int16_t pixelY[]= {  0, 0, 500, 1000, 300, 200, 500, 0};
*/
//arraySize = 726;
int arraySize = 726; //cantidad de fijaciones
int n = 1;
int m = 0;
unsigned long puntero = 0;
int anchoHoja = 1900; //SheetWidth

//variables correspondientes al motor
int velocidadXY = 500; //velocidadXY en microsegundos
int velocidadZ = 500; //velocidadZ en microsegundos
//motor Z
const int pinStepsZ = 3;
const int pinDirZ = 2;
const int pinResetZ = 4; //10;
int pasosZ = 125;
int tQuemado = 1000; // milisegundos de quemado
//X
const int pinStepsX = 11; //5;
const int pinDirX = 10; //6;
const int pinResetX = 12; //12;
//Y
const int pinStepsY = 6; //29;
const int pinDirY = 5; //27;
const int pinResetY = 7; //31;
//boton on
const int pinSensor = 24; //20;
int valSensor = LOW;
int oldvalSensor = LOW;
int stateSensor = 0;
int flag = LOW;

//finales de carrera
const int endStopX = A0;
const int umbralEndStopX = 10;
int valEnd_X;

const int endStopY = A1;
const int umbralEndStopY = 10;
int valEnd_Y;

const int endStopZ = 27;

int valEnd_Z = LOW;

int flag_endX = LOW;
int flag_endY = LOW;
int flag_endZ = LOW;

long counter_x = 0; //Contador de ejecución de paso, en X
long counter_y = 0; //Contador de ejecución de paso, en Y


/*factor de conversión de pixel a pasos
    1000 pasos son 6,2 mm(de motor paso a paso de brida 28mm con acople de 5mm a 8mm y
  varilla roscada de 8mm)
  como convertir pixeles a pasos:
  (159mm(ancho de formato de texto)* 1000pap/ 6.2mm)/ 1890px (ancho en pixeles) = f
  (159mm(ancho de formato de texto)* 1000pap/ 6.2mm)= 25645,16 (cantidad de pasos necesarios para recorrer el ancho del formato del texto)
  25646,16 / 1890px = 13.56 = f */
float f = 9 ;
//int f = 13;

long posX = 0; //Pasos convertidos a partir de la variable en X
long posY = 0; //Pasos convertidos a partir de la variable en Y
long posXpasos = 0;
long posYpasos = 0;
long posAntX = 0; //PosX del anterior loop
long posAntY = 0; //PosY del anterior loop


//VARIABLES SENSOR ldr
boolean leerHoja = true; //ReadSheet
boolean flagPrendoMotorRollo = false;//FlagEnableRollMotor
boolean salir_de_marca = true;// ExitMark
boolean flag_temperatura = false;// FlagTemperature

///MOTOR rollo arriba
const int pinDirUp = 30; //42; //AZUL 45
const int pinStepsUp = 28; //40; //ROJO 43
const int pinResetUp = 26; //38; //VERDE 41

///MOTOR rollo abajo
const int pinDirDown = 38;//51; //51; //AZUL 51
const int pinStepsDown = 36;//48; //49; //ROJO 49
const int pinResetDown = 34;//46; //47; //VERDE 47

int velocidadRollo = 16000;//chequear con nuevos motores.

int pote;
int ldr;
int led = A0; //13;

int sensorTemperatura = 0; //TemperatureSensor
const int pinTemperatura = 41; //33; //TemperaturePin
int contador_ciclo_temperatura = 3;//arranca solo si está en 3, en 0 cuenta el prendido del quemador

int flag_buscar_cero = true;// FlagFindZero
int flag_prender_motores = HIGH; //FlagEnableMotors

//variables para utilizar la memoria SD
File myFileX, myFileY, punX, punY;//archivos de texto
unsigned long punteroX, punteroY = 0;
boolean flag_posAntX = true;
boolean flag_posAntY = true;
int r = 0;

void setup() {
  Serial.begin(115200);
  // initialize the digital pin as an output.
  pinMode(pinStepsZ, OUTPUT);
  pinMode(pinDirZ, OUTPUT);
  pinMode(pinResetZ, OUTPUT);
  pinMode(pinStepsX, OUTPUT);
  pinMode(pinDirX, OUTPUT);
  pinMode(pinResetX, OUTPUT);
  pinMode(pinStepsY, OUTPUT);
  pinMode(pinDirY, OUTPUT);
  pinMode(pinResetY, OUTPUT);

  //digitalWrite(pinResetZ, HIGH);
  digitalWrite(pinResetY, LOW);
  digitalWrite(pinResetX, LOW);

  // faltan 3 sensores de final de carrera
  pinMode(pinSensor, INPUT);
  pinMode(endStopX, INPUT);
  pinMode(endStopY, INPUT);
  pinMode(endStopZ, INPUT);
  //  Serial.println("ESPERANDO COMANDO DE ENCENDIDO");

  ///SENSORes
  pinMode(led, OUTPUT);
  pinMode(pinTemperatura, INPUT);

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
  //poner al sistema en cero (0,0,0)
  //funcion cero
  //libero motor abajo del rollo
  digitalWrite(pinResetDown, LOW);

  //memoria SD
  Serial.begin(9600);
  Serial.println("Inicializando SD...");

  if (SD.begin()) { //esto aprueba que la memoria SD está disponible
    Serial.println("OK...");
    getPunteroX();
    getPunteroY();
    /*
      myFileX = SD.open("pixelX.txt");
      //myFileX.seek(punteroX); //pongo el puntero en 0
      myFileY = SD.open("pixelY.txt");
      //myFileY.seek(punteroY); //pongo el puntero en 0 */
  }
  else {
    Serial.println("No encuentra archivo");
    delay(500);
  }

  delay(5000); //para que no arranque directo
  digitalWrite(pinResetZ, HIGH);
  sequenceUp();
}

void loop() {
  //Esperar que la resistencia caliente
  contarCiclosTemperatura();
  // BUSCAR EL (0,0)
  if (flag_buscar_cero == HIGH) {
    buscar_cero();
  }
  //a partir de acá la maquina está lista para quemar
  quemar();
}

void quemar() {
  if ((contador_ciclo_temperatura > 2) && (flag_buscar_cero == LOW)) {
    valSensor = HIGH;//digitalRead(pinSensor);//leo el boton de encendido
    //    flag == LOW;
    if ((valSensor == HIGH) && (flag == LOW)) {
      //arrayRead();
      arrayReadSD();
      // digitalWrite prepara los motores para mover
      //secuencia de encendido()
      digitalWrite(pinResetZ, HIGH);
      digitalWrite(pinResetY, HIGH);
      digitalWrite(pinResetX, HIGH);
      valSensor = digitalRead(pinSensor);
      flag = HIGH;
      //    Serial.println("ENCENDIDO");
    }
    /*if ((valSensor == HIGH) && (flag == HIGH)) {
      flag = LOW;
      //delay(1000);
      //    Serial.println("APAGADO");
      }*/
    if ( leerHoja == true) { //empieza a quemar
      //apagar motores de rollo una vez
      if (flagPrendoMotorRollo == false) {
        digitalWrite(pinResetUp, LOW);
        digitalWrite(pinResetDown, LOW);
        flagPrendoMotorRollo = true;
      }
      //movimiento de motores en X e Y
      if (flag == HIGH) {
        if (posXpasos > 0) {
          digitalWrite(pinDirX, HIGH);
          if (counter_x < posXpasos) {
            mueve(pinStepsX, velocidadXY);
            counter_x++;
          }
        }
        else if (posXpasos < 0) {
          digitalWrite(pinDirX, LOW);
          if (counter_x < (-posXpasos)) {
            mueve(pinStepsX, velocidadXY);
            counter_x++;
          }
        }
        if (posYpasos > 0) {
          digitalWrite(pinDirY, HIGH);
          if (counter_y < posYpasos) {
            mueve(pinStepsY, velocidadXY);
            counter_y++;
          }
        }
        else if (posYpasos < 0) {
          digitalWrite(pinDirY, LOW);
          if (counter_y < (-posYpasos)) {
            mueve(pinStepsY, velocidadXY);
            counter_y++;
          }
        }
      }
    }

    if (leerHoja == false) {//si no esta leyendo, ir a nueva pagina
      sensar_hoja();//Sensar hoja, para saber si esta en una marca o no
    }
    if (counter_x == abs(posXpasos) && counter_y == abs(posYpasos)) { //si llego al lugar de la fijacion
      sequenceDown();//marco la fijacion
      counter_x = 0;
      counter_y = 0;
      m = n;
      n++;//avanzo una posición en el array
      if (n == arraySize) {
        /*
          leerHoja = false; //terminó de quemar la hoja
          salir_de_marca = true;
          flagPrendoMotorRollo = true;
        */
        n = 1;
        //buscar_cero();
        punteroX = 0;
        punteroY = 0;
      }
      //arrayRead(); //busca una nueva posición
      arrayReadSD();
    }
  }
}

void contarCiclosTemperatura() {
  sensorTemperatura = digitalRead(pinTemperatura);
  //secuencia para contar ciclos de prendido y apagado de la resistencia
  if (sensorTemperatura == LOW && flag_temperatura == false ) {
    contador_ciclo_temperatura++;
    flag_temperatura = true;
  }
  if (sensorTemperatura == HIGH && flag_temperatura == true ) {
    contador_ciclo_temperatura++;
    flag_temperatura = false;
  }
}

void prenderMotoresXY() {
  if ((flag_buscar_cero == HIGH) && (flag_prender_motores == HIGH)) {
    digitalWrite(pinResetY, HIGH);
    digitalWrite(pinResetX, HIGH);
    flag_prender_motores = LOW;
  }
}

void mueve(int pinStep, int velocidad) {
  digitalWrite(pinStep, HIGH);
  delayMicroseconds(velocidad);
  digitalWrite(pinStep, LOW);
  delayMicroseconds(velocidad);
}

void sequenceDown() {
  turnOffXY();
  digitalWrite(pinDirZ, HIGH);
  for (int i = 0; i < pasosZ; i++) {
    mueve(pinStepsZ, velocidadZ);
  }
  delay(tQuemado);
  sequenceUp();
  turnOnXY();
}

void sequenceUp() {
  digitalWrite(pinDirZ, LOW);
  for (int i = 0; i < pasosZ; i++) {
    mueve(pinStepsZ, velocidadZ);
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

void arrayRead() {
  //m = n - 1; //m es la posición anterior

  posX = pgm_read_word_near(pixelX + n);
  posXpasos = (posX - pgm_read_word_near(pixelX + m)) * f; //posX = cantidad de pasos en "x" que debe efectuar para ir a destino

  posY = pgm_read_word_near(pixelY + n);
  posY = (posY - pgm_read_word_near(pixelY + m)) * f; //posY = cantidad de pasos en "y" que debe efectuar para ir a destino
}

void setPuntero() { //cada vez que arranca se fija en cuanto quedó el puntero de cada archivo
  punX = SD.open("punteroX.txt", FILE_WRITE); //cuando abro el archivo para escribirlo es que se traba
  punX.seek(0);//me posiciono en el inicio del archivo
  punX.print(punteroX);//escribe la nueva posicion del puntero
  //Serial.print(" punteroX: ");
  //Serial.print(punteroX);
  punX.close();

  punY = SD.open("punteroY.txt", FILE_WRITE);
  punY.seek(0);//me posiciono en el inicio del archivo
  punY.print(punteroY);//escribe la nueva posicion del puntero
  //Serial.print(", punteroY: ");
  //Serial.println(punteroY);
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
  //solo hago getPuntero() si se cortó la luz
  //getPunteroX();//obtengo la ultima posicion del punteroX
  myFileX = SD.open("h1x.txt", FILE_READ);//abro el archivo de fijaciones en X
  myFileX.seek(punteroX);//posiciono el puntero
  if (myFileX.available() > 0) {
    Serial.print(" Entrando al archivo X");
    if (flag_posAntX) { //si es la primera, agarro la primera como anterior
      posAntX = myFileX.parseInt();//agarro la posicion inicial, para hacer el calculo
      flag_posAntX = false;//flag para hacerlo solo la primera vez
    }
    posX = myFileX.parseInt(); //separa los numeros y lo guarda en posX
    punteroX = myFileX.position(); //agarra la posicion actual
    myFileX.close();

    Serial.print(", valAntX: ");
    Serial.print(posAntX);
    Serial.print(", valX: ");
    Serial.println(posX);
  } else { //si terminó de leer el archivo
    Serial.println("termino el archivo");
    punteroX = 0;//me posiciono de vuelta en 0
    myFileX.close();//guardo y cierro
  }

  posXpasos = (posX - posAntX) * f;//variable con la cantidad de pasos de motor
  //posXpasos = (posAntX - posX) * f;
  posAntX = posX; //actualizo el valor anterior

  //getPunteroY();//obtengo la ultima posicion del punteroY
  myFileY = SD.open("h1y.txt", FILE_READ);//abro el archivo de fijaciones en Y
  myFileY.seek(punteroY);//posiciono el puntero
  if (myFileY.available() > 0) {
    Serial.print(" Entrando al archivo Y");
    if (flag_posAntY) {//si es la primera, agarro la primera como anterior
      posAntY = myFileY.parseInt();//agarro la posicion inicial, para hacer el calculo
      flag_posAntY = false;//flag para hacerlo solo la primera vez
    }
    posY = myFileY.parseInt(); //separa los numeros y lo guarda en posY
    punteroY = myFileY.position(); //agarra la posicion actual
    myFileY.close();//guardo y cierro

    Serial.print(", valAntY: ");
    Serial.print(posAntY);
    Serial.print(", valY: ");
    Serial.println(posY);
  } else {
    Serial.println("termino el archivo");
    punteroY = 0;//me posiciono de vuelta en 0
    myFileY.close();//guardo y cierro
  }
  posYpasos = (posY - posAntY) * f;//variable con la cantidad de pasos de motor
  //posYpasos = (posAntX - posX) * f;
  posAntY = posY;//actualizo el valor anterior
  r++;
  if (r > 10) { //guardo el puntero cada X fijaciones
    setPuntero();//actualizo los punteros
    r = 0;
  }
}

void buscar_cero() {
  prenderMotoresXY();//Prendo motores para buscar el cero
  valEnd_X = analogRead(endStopX);//leo fin de carrera en X
  //fin de carrera en X
  if ((valEnd_X > umbralEndStopX) && (flag_endX == LOW)) {
    // Fijarse la direccion de X
    digitalWrite(pinDirX, HIGH);
    mueve(pinStepsX, velocidadXY);
  }
  if (valEnd_X < umbralEndStopX) {
    flag_endX = HIGH;
    digitalWrite(pinResetX, LOW); //apago motorX
  }
  //fin de carrera en Y
  valEnd_Y = analogRead(endStopY); //leo fin de carrera en Y
  if ((valEnd_Y > umbralEndStopY) && (flag_endY == LOW)) {
    // Fijarse la direccion de X
    digitalWrite(pinDirY, LOW);
    mueve(pinStepsY, velocidadXY);
  }
  if (valEnd_Y < umbralEndStopY) {
    flag_endY = HIGH;
    digitalWrite(pinResetY, LOW);
  }

  if ((flag_endX == HIGH) && (flag_endY == HIGH)) { //si tocaron ambos fines de carrera ya está en 0,0
    flag_buscar_cero = LOW;
  }
}

void sensar_hoja() {
  //me fijo si el ldr detecta la marca
  if (salir_de_marca == true) {
    digitalWrite(pinResetUp, HIGH);
    for (int i = 0; i < 50; i++) {
      mueve(pinStepsUp, velocidadRollo);
    }
    salir_de_marca = false;
  }
  pote = analogRead(A4); //usado para calibración
  ldr = analogRead(A7);
  if (flagPrendoMotorRollo == true) {
    digitalWrite(pinResetUp, HIGH);
    digitalWrite(pinDirUp, LOW);
    flagPrendoMotorRollo = false;
  }
  mueve(pinStepsUp, velocidadRollo);
  if (ldr > pote) { //si detecta marca, hay que leer nueva hoja
    digitalWrite(led, HIGH);
    leerHoja = true;
  }
  else {
    digitalWrite(led, LOW);
  }
}
