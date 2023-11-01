#include <SD.h>

#define sw1 31 
#define sw2 17 
#define buzzerPin PB_2

File Data; // Variable para el archivo de datos
String DataDeTemperatura; // Almacena los datos de temperatura

void setup() {
  Serial.begin(115200);
  Serial2.begin(115200);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(sw2, INPUT_PULLUP); 
  pinMode(buzzerPin, OUTPUT); 
  if (!SD.begin(4)) { // Configura el pin CS para el módulo microSD (en este caso, pin 4)
//Serial.println("No se pudo inicializar la tarjeta SD");
  //while (false); // Detén el programa si no se puede inicializar la tarjeta SD
  }
}

void loop() {
  if (Serial2.available() > 0) {
    char Cel = Serial2.read();
    Serial.write(Cel);
  }

  if (digitalRead(sw1) == LOW) {
    Serial.println("Medición");
    Serial2.println('c');
    delay(1000);
    DataDeTemperatura = Serial.readString(); 
    Sonido(1000); // Reproduce un sonido al presionar sw1
  }

  if (digitalRead(sw2) == LOW) {
    // Si el botón SW2 se presiona, guarda los datos en la tarjeta microSD
    GuardarT();
    Sonido(2500); // Reproduce un sonido diferente al presionar sw2
  }
}

void Sonido(int duracionB) {
  tone(buzzerPin, 1000, duracionB); 
  delay(duracionB);
  noTone(buzzerPin); 
}

void GuardarT() {
  Data = SD.open("temperatura.txt", FILE_WRITE); // Abre el archivo de modo texto

  if (Data) {
    Data.println(DataDeTemperatura); // Escribe los datos de temperatura en el archivo
    Data.close(); // Cierra el archivo
    Serial.println("Datos de temperatura guardados en la tarjeta SD");
  } else {
    Serial.println("No se pudo guardar los datos correctamente");
    delay(1000);
  }
}
