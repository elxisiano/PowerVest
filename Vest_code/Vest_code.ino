#define LED 13

#define FSR_0 A0 //Sensor Pecho
#define FSR_1 A1 //Sensor Abdomen
#define FSR_2 A5 //Sensor Lateral izq.
#define FSR_3 A3 //Sensor Lateral der.

int aux0 = 0;
int aux1 = 0;
int aux2 = 0;
int aux3 = 0;

int sensivity0 = 600; //Sensibilidad para el Pecho
int sensivity1 = 600; //Sensibilidad para el Abdomen
int sensivity2 = 600; //Sensibilidad para el Lateral izquierdo
int sensivity3 = 600; //Sensibilidad para el Lateral derecho

char simple = 'L';
char doble = 'D';

boolean pinEstado = 0;

void setup() {
  // Configuración del puerto Serie para monitor
  Serial.begin(9600);
  Serial.flush();
  //Serial.print("Serial OK");
  // Configuración de los pines
  pinMode(FSR_0, INPUT);
  pinMode(FSR_1, INPUT);
  pinMode(FSR_2, INPUT);
  pinMode(FSR_3, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
   aux0 = analogRead(FSR_0); // Leer del puerto AO
   aux1 = analogRead(FSR_1); // Leer del puerto A1
   aux2 = analogRead(FSR_2); // Leer del puerto A2
   aux3 = analogRead(FSR_3); // Leer del puerto A3

   //Serial.println(aux0); // Trazas para debuggear
   
   if(aux0>sensivity0){
    //Serial.println("Golpe en el pecho"); // Mostrar mensaje por el monitor
    Serial.flush();
    Serial.write(simple);
    delay(168);
   }

   if(aux1>sensivity1){
    //Serial.println("Golpe en el abdomen"); // Mostrar mensaje por el monitor
    Serial.flush();
    Serial.write(simple);
    delay(168);
   }

   if(aux2>sensivity2){
    //Serial.println("Golpe en el lateral izquierdo"); // Mostrar mensaje por el monitor
    Serial.flush();
    Serial.write(simple);
    delay(168);
   }

   if(aux3>sensivity3){
    //Serial.println("Golpe en el lateral derecho"); // Mostrar mensaje por el monitor
    Serial.flush();
    Serial.write(simple);
    delay(168);
   }
   
   toggle(LED); // Cambiar el estado del LED
}

// Función que cambia el estado de un pin. Se utiliza para la detección de
// errores y comprobación de la comunicación bidireccional con el
// dispositivo Bluetooth remoto.
void toggle(int pinNum) {
  // Establece el pin del LED usando la variable pinEstado:
  digitalWrite(pinNum, pinEstado); 
  // si el pinEstado = 0, lo establece a 1, y viceversa:
  pinEstado = !pinEstado;
}
