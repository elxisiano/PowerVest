/*
 *  Author: Diego E. Manceras Vico
 *  Date  : 10.10.2015
 */
 
#include <SoftwareSerial.h>
#include <Adafruit_GFX.h>   // Core graphics library
#include <RGBmatrixPanel.h> // Hardware-specific library

//#define BT_TX 11
//#define BT_RX 10
//#define BT2_TX 12
//#define BT2_RX 13

#define CLK 11  // MUST be on PORTB! (Use pin 11 on Mega)
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel matrix(A, B, C, CLK, LAT, OE, false);

unsigned int counter1 = 0;  // Variable que almacena el numero de golpes 1
unsigned int counter2 = 0;  // Variable que almacena el numero de golpes 2

String cadena1 = String();
String cadena2 = String();

//SoftwareSerial BT_Serial(BT_RX, BT_TX);
//SoftwareSerial BT2_Serial(BT2_RX, BT2_TX);

boolean pinEstado = 0;

int timepo = 0;


void setup() {
  
  Serial.begin(9600);
  
  //Serial.println("Puerto serie para comunicacion punto a punto funcionando...");

  Serial1.begin(9600);
  //Serial.println("Puerto serie (software) de comunicacion Bluetooth funcionando...");
  Serial1.flush();

  Serial2.begin(9600);
  //Serial.println("Puerto serie (software) de comunicacion Bluetooth funcionando...");
  Serial2.flush();

  analogReference(EXTERNAL);
  matrix.begin();

  matrix.setTextSize(1);
  
  matrix.setCursor(2, 5);
  matrix.setTextColor(matrix.Color444(15,15,0));
  matrix.print("READY");

  matrix.fillScreen(0);
  
  matrix.setCursor(3,5);
  matrix.setTextColor(matrix.Color444(0,12,0));
  cadena1 = cadena1 +  "0" + String(counter1);
  matrix.print(cadena1);

  matrix.setCursor(18,5);
  matrix.setTextColor(matrix.Color444(12,0,0));
  cadena2 = cadena2 + "0" + String(counter2);
  matrix.print(cadena2);
  
}


void loop() {
  // Espera a recibir datos por el puerto serie (software) al que está conectado
  // el Bluetooth.
 
  cadena1="";
  cadena2="";




  // La funcion read() devuelve un caracter 
  char command = Serial2.read();
  Serial.println(command);
  //Serial.println(command);
  Serial2.flush();
  delay(50);
  
  if (command == 'L') {
    counter1++;
    delay(10);
    //repaint();
  
    imprimir_pantalla(counter1, counter2);
    
    //sendCounter();
    //toggle(LED);
    //Serial.println("Recibido (Simple)");
    delay(10);
  }
  
  if (command == 'D') {
    counter1 = counter1 + 2;
    delay(10);
    //sendCounter();
    //Serial.println("Recibido (Doble)");
    delay(10);
  }
    
  
  
  // La funcion read() devuelve un caracter 
  command = Serial1.read();
  //Serial.println(command);
  Serial1.flush();
  delay(50);
  
  if (command == 'L') {
    counter2++;
    delay(10);
    //repaint();
  
    imprimir_pantalla(counter1, counter2);
    
    //sendCounter();
    //toggle(LED);
    //Serial.println("Recibido (Simple)");
    delay(10);
  }
  
  if (command == 'D') {
    counter2 = counter2 + 2;
    delay(10);
    //sendCounter();
    //Serial.println("Recibido (Doble)");
    delay(10);
  }
 
}
 
  


void imprimir_pantalla(int counter1, int counter2){

  matrix.fillScreen(0);
      
  matrix.setCursor(3,5);
  matrix.setTextColor(matrix.Color444(0,12,0));
  
  if(counter1 < 10)
    cadena1 = cadena1 +  "0" + String(counter1);
  else if(counter1 >= 10)
    cadena1 = cadena1 + String(counter1);
    
  matrix.print(cadena1);
  
  matrix.setCursor(18,5);
  matrix.setTextColor(matrix.Color444(12,0,0));
  
  if(counter2 < 10)
    cadena2 = cadena2 +  "0" + String(counter2);
  else if(counter2 >= 10)
    cadena2 = cadena2 + String(counter2);
    
  matrix.print(cadena2);
  
}


//void sendCounter() {
//  Serial.flush();
//  Serial.write(counter1);
//  Serial.flush();
//}


// Función que cambia el estado de un pin. Se utiliza para la detección de
// errores y comprobación de la comunicación bidireccional con el
// dispositivo Bluetooth remoto.
void toggle(int pinNum) {
  // Establece el pin del LED usando la variable pinEstado:
  digitalWrite(pinNum, pinEstado); 
  // si el pinEstado = 0, lo establece a 1, y viceversa:
  pinEstado = !pinEstado;
}
