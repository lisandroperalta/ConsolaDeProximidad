


/* SENSOR 01*/
const int LDRPin1 = A1;  //Pin del LDR
int V1;
int ilum1;
const int ilum1_max = 600;  //<-------------- VALOR MAXIMO
const int ilum1_min = 50;   //<-------------- VALOR MINIMO (50 esta bien para que no tartamudee)
int brightness_01 = 0;
int V_Anterior_01 = 0;

/* SENSOR 02*/
const int LDRPin2 = A2;  //Pin del LDR
int V2;
int ilum2;
const int ilum2_max = 600;  //<-------------- VALOR MAXIMO
const int ilum2_min = 50;    //<-------------- VALOR MINIMO (50 esta bien para que no tartamudee)
int brightness_02 = 0;
int V_Anterior_02 = 0;


/* SENSOR 03*/
const int LDRPin3 = A3;  //Pin del LDR
int V3;
int ilum3;
const int ilum3_max = 600;  //<-------------- VALOR MAXIMO
const int ilum3_min = 50;    //<-------------- VALOR MINIMO (50 esta bien para que no tartamudee)
int brightness_03 = 0;
int V_Anterior_03 = 0;


/* SENSOR 04*/
const int LDRPin4 = A4;  //Pin del LDR
int V4;
int ilum4;
const int ilum4_max = 600;  //<-------------- VALOR MAXIMO
const int ilum4_min = 50;   //<-------------- VALOR MINIMO (50 esta bien para que no tartamudee)
int brightness_04 = 0;
int V_Anterior_04 = 0;

/*COSAS DEL DMX*/
#include <DmxSimple.h>


void setup() {
  Serial.begin(115200);

  /* The most common pin for DMX output is pin 3, which DmxSimple
  ** uses by default. If you need to change that, do it here. */
  DmxSimple.usePin(3);

  /* DMX devices typically need to receive a complete set of channels
  ** even if you only need to adjust the first channel. You can
  ** easily change the number of channels sent here. If you don't
  ** do this, DmxSimple will set the maximum channel number to the
  ** highest channel you DmxSimple.write() to. */
  DmxSimple.maxChannel(4);
}

void loop() {



  V1 = analogRead(LDRPin1);
  V2 = analogRead(LDRPin2);
  V3 = analogRead(LDRPin3);
  V4 = analogRead(LDRPin4);

  V1 = lerp(V_Anterior_01, V1, 0.05);
  V_Anterior_01 = V1;
  brightness_01 = map(V1, ilum1_min, ilum1_max, 255, 0);
  brightness_01 = constrain(brightness_01, 0, 255);


  V2 = lerp(V_Anterior_02, V2, 0.05);
  V_Anterior_02 = V2;
  brightness_02 = map(V2, ilum2_min, ilum2_max, 255, 0);
  brightness_02 = constrain(brightness_02, 0, 255);


  V3 = lerp(V_Anterior_03, V3, 0.5);
  V_Anterior_03 = V3;
  brightness_03 = map(V3, ilum3_min, ilum3_max, 255, 0);
  brightness_03 = constrain(brightness_03, 0, 255);

  V4 = lerp(V_Anterior_04, V4, 0.05);
  V_Anterior_04 = V4;
  brightness_04 = map(V4, ilum4_min, ilum4_max, 255, 0);
  brightness_04 = constrain(brightness_04, 0, 255);
  
  if (millis() % 100 == 0) {
    /*CREO QUE TENGO QUE DESACTIVAR ESTO DE SERIAL PRINT*/
    Serial.print(V1);
    Serial.print(",");
    Serial.print(V2);
    Serial.print(",");
    Serial.print(V3);
    Serial.print(",");
    Serial.println(V4);
  }

  //delay(100);


  DmxSimple.write(1, brightness_01);
  DmxSimple.write(2, brightness_02);
  DmxSimple.write(3, brightness_03);
  DmxSimple.write(4, brightness_04);

  /* Update DMX channel 1 to new brightness */
}

/* MI LERP */

float lerp(float start, float end, float t) {
  return start + t * (end - start);
}
