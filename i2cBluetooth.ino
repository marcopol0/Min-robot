#include <Wire.h>

//#include <SoftwareSerial.h>

//SoftwareSerial mySerial(10, 11);
const byte TRIGGER_PIN = 4; // Broche TRIGGER
const byte ECHO_PIN = 3;    // Broche ECHO
long mm;
const long MEASURE_TIMEOUT = 25000L; // 40Hz = 25ms = ~8m à 340m/s

static byte x = 0x05;
static char c = '5';



void setup() {

  
  //Serial.begin(9600);
   
  /* Initialisation des broches */
  pinMode(TRIGGER_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  digitalWrite(TRIGGER_PIN, LOW); // DOIT être à LOW au repos
  //mySerial.begin(9600);
  /*communication i2c*/
  Wire.begin();
  Serial.begin(9600);
   
}

void loop() {
 
  digitalWrite(TRIGGER_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGGER_PIN, LOW);
  // 2) Mesure le temps entre l'envoi de l'impulsion ultrasonique et son écho (si il existe) 
  long measure = pulseIn(ECHO_PIN, HIGH, MEASURE_TIMEOUT);
  // 3) Calcul la distance à partir du temps mesuré 
  mm = measure / 2 * 0.3434;
  //Serial.println ("loop");
  
   if (Serial.available()> 0)
   // wait for character to arrive
  {
     c = Serial.read();
   
      if(c =='1') {
       x = 0x01;   // set the LED on
      }
      else if(c == '2'){
         x = 0x02;
      }
      else if (c=='3')
      {
         x = 0x03;
      }
      else if (c=='4')
      {
         x = 0x04;
      }
      else if (c == '5')
      {
         x = 0x05;
      }
     else
      {
        x = x;
      } 
     }  
 
  
  
  Wire.beginTransmission(8);
  if (mm < 200)
  {
    c= '5';
    x = 0x05;
  }
  //Serial.println (x);
  Wire.write(x);
  //Serial.println ("message envoye");
  Wire.endTransmission(); 
  delay (10);
  
}


