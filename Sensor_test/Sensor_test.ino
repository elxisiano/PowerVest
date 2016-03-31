#define LED 13
#define FSR_0 A0 //Conectar el sensor al Pin A0

int aux0 = 0;
boolean pinEstado = 0;

void setup() {
  // Configuración del puerto Serie para monitor
  Serial.begin(9600);
  Serial.print("Serial OK");
  // Configuración de los pines
  pinMode(FSR_0, INPUT);
  pinMode(LED, OUTPUT);
}

void loop() {
   aux0 = analogRead(FSR_0); // Leer del puerto AO
   Serial.println(aux0); // Mostrar el valor por el monitor
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
