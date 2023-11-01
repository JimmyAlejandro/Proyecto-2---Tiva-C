#include <Arduino.h>

const int sensor = 34;

float temperatura = 0.0;

//void medirSensor(void);
//String bufferTiva;
//int valorSensor = 0;


void setup() {
  Serial.begin(115200); // Inicializar la comunicación UART a 115200 bps
  Serial2.begin(115200);

  //pinMode(sensor, INPUT);
}

void loop() {

    while (Serial2.available() > 0) {
    char Cel = Serial2.read(); // Leer un carácter de la UART
    if(Cel == 'c')
    {

      //Serial.println(temperatura);
      
          int Sensorvalor = analogRead(sensor);
          float V = (Sensorvalor / 4095.0) * 3300.0; // ADC a mV

          V = V + 200.0; //Offset a la lectura para tener el valor ajustado de temperatura

          temperatura = V / 19.0; //Calibración del sensor

          //if (temperatura < 25){
          //temperatura = 25;
          //}
           //Serial.print("temperatura: ");
           //Serial.print(temperatura);
           //Serial.println(" °C");

           //delay(1000); // Delay para el botón

            

            Serial.print("La medición del sensor es: ");
            Serial2.println(temperatura);
            Serial.println(temperatura);
    }


  }
}
