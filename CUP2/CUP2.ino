
#include <NewPing.h>
#define TRIGGER_PIN  18  // Arduino pin tied to trigger pin on the ultrasonic sensor.
#define ECHO_PIN     19  // Arduino pin tied to echo pin on the ultrasonic sensor.
#define MAX_DISTANCE 2500 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum d

// I2C Library
#include <Wire.h>
// HMC5883L Compass Library
#include <HMC5883L.h>
HMC5883L compass;
// grava qqr erro que de no compasso
int error = 0;

MagnetometerScaled valueOffset;

  
const int M1A1=8;
const int M1A2=9;
int M2A1=6; 
int M2A2=7;

int M3A1=2;
int M3A2=3;

int M4A1=4;
int M4A2=5;

int DRIBLE1=10;
int DRIBLE2=11;
int CHUTE=23;
int BOTAO=17;
int ESTADOBOTAO=0;
int libera=0;
int LED_G=14;
int LED_Y=15;
int LED_R=69;


void setup() {

 Serial.begin(9600);
  delay(1000);
  Serial.println("Inicializando interface I2C.");
  Wire.begin(); // INICIALIZANDO MODULO I2C.

  Serial.println("Robotica 2018 CAZECA");
    
  Serial.println("Setando escala em  +/- 1.3 Ga");
  error = compass.setScale(1.3); // Set the scale of the compass.
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.getErrorText(error));
  
  Serial.println("modo continuo de medicao selecionado.");
  error = compass.setMeasurementMode(MEASUREMENT_CONTINUOUS); // Set the measurement mode to Continuous
  if(error != 0) // If there is an error, print it out.
    Serial.println(compass.getErrorText(error));
    
  compassCalibrate();

  pinMode(M1A1 , OUTPUT);
  pinMode(M1A2 , OUTPUT); 
  pinMode(M2A1 , OUTPUT);
  pinMode(M2A2 , OUTPUT); 
  pinMode(M3A1 , OUTPUT);
  pinMode(M3A2 , OUTPUT); 
  pinMode(M4A1 , OUTPUT);
  pinMode(M4A2 , OUTPUT); 
  pinMode(DRIBLE1 , OUTPUT);
  pinMode(DRIBLE2 , OUTPUT); 
  pinMode(CHUTE , OUTPUT);
  pinMode(LED_G, OUTPUT);
  pinMode(LED_Y , OUTPUT);
  pinMode(LED_R, OUTPUT);
  pinMode(BOTAO, INPUT);
 digitalWrite(CHUTE, HIGH);
  
  
}

void loop() {

 delay(50);                     // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  Serial.print("Distancia: ");
 Serial.print(sonar.ping_cm()); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");

ESTADOBOTAO = digitalRead(BOTAO);


 // Retrive the raw values from the compass (not scaled).
  MagnetometerRaw raw = compass.readRawAxis();
  // Retrived the scaled values from the compass (scaled to the configured scale).
  MagnetometerScaled scaled = compass.readScaledAxis();
  
  scaled.XAxis -= valueOffset.XAxis;
  scaled.YAxis -= valueOffset.YAxis;
  scaled.ZAxis -= valueOffset.ZAxis;
  
  // Values are accessed like so:
  int MilliGauss_OnThe_XAxis = scaled.XAxis;// (or YAxis, or ZAxis)

  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  float yxHeading = atan2(scaled.YAxis, scaled.XAxis);
  float zxHeading = atan2(scaled.ZAxis, scaled.XAxis);
  
  float heading = yxHeading;
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -2��37' which is -2.617 Degrees, or (which we need) -0.0456752665 radians, I will use -0.0457
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off.
  float declinationAngle = -0.0457;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  float headingDegrees = heading * 180/M_PI; 
  
  float yxHeadingDegrees = yxHeading * 180 / M_PI;
  float zxHeadingDegrees = zxHeading * 180 / M_PI;

  // Output the data via the serial port.
  // Output(raw, scaled, heading, headingDegrees);
  
//  Serial << scaled.XAxis << ' ' << scaled.YAxis << ' ' << scaled.ZAxis << endl;
//  Serial << "arctan y/x: " << yxHeadingDegrees << " \tarctan z/x: " << zxHeadingDegrees << endl;
  
  Serial.print(scaled.XAxis);
  Serial.print(scaled.YAxis);
  Serial.println(scaled.ZAxis);
  
  Serial.print("arctan y/x: ");
  Serial.print(yxHeadingDegrees);
  Serial.print("arctan z/x: ");  
  Serial.print(zxHeadingDegrees);
  
  // Normally we would delay the application by 66ms to allow the loop
  // to run at 15Hz (default bandwidth for the HMC5883L).
  // However since we have a long serial out (104ms at 9600) we will let
  // it run at its natural speed.
  delay(1000);//of course it can be delayed longer.
}

// Output the data down the serial port.
void Output(MagnetometerRaw raw, MagnetometerScaled scaled, float heading, float headingDegrees)
{
   Serial.print("Raw:\t");
   Serial.print(raw.XAxis);
   Serial.print("   ");   
   Serial.print(raw.YAxis);
   Serial.print("   ");   
   Serial.print(raw.ZAxis);
   Serial.print("   \tScaled:\t");
   
   Serial.print(scaled.XAxis);
   Serial.print("   ");   
   Serial.print(scaled.YAxis);
   Serial.print("   ");   
   Serial.print(scaled.ZAxis);

   Serial.print("   \tHeading:\t");
   Serial.print(heading);
   Serial.print(" Radians   \t");
   Serial.print(headingDegrees);
   Serial.println(" Degrees   \t");


//LED TESTE
digitalWrite(LED_G, HIGH);
delay(100);
digitalWrite(LED_Y, HIGH);
delay(100);
digitalWrite(LED_R, HIGH);
delay(100);
digitalWrite(LED_G, LOW);
delay(100);
digitalWrite(LED_Y, LOW);
delay(100);
digitalWrite(LED_R, LOW);
delay(100);


if(ESTADOBOTAO == LOW){

  
//MOTOR 1 TESTE
digitalWrite(M1A1, HIGH);
analogWrite(M1A2, 178);//30%
delay(2000);
digitalWrite(M1A1, LOW);
analogWrite(M1A2, 76);//30%
delay(2000);
  
//MOTOR 2 TESTE
digitalWrite(M2A1, HIGH);
analogWrite(M2A2, 178);
delay(2000);
digitalWrite(M2A1, LOW);
analogWrite(M2A2, 76);
delay(2000);


//MOTOR 3 TESTE
digitalWrite(M3A1, HIGH);
analogWrite(M3A2, 178);
delay(2000);
digitalWrite(M3A1, LOW);
analogWrite(M3A2, 76);
delay(2000);

  
//MOTOR 4 TESTE
digitalWrite(M4A1, HIGH);
analogWrite(M4A2, 178);
delay(2000);
digitalWrite(M4A1, LOW);
analogWrite(M4A2, 76);
delay(2000);

  
//MOTOR 2 TESTE
digitalWrite(DRIBLE1, HIGH);
analogWrite(DRIBLE2, 178);
delay(2000);
digitalWrite(DRIBLE1, LOW);
analogWrite(DRIBLE2, 76);
delay(2000);


//CHUTE TESTE
digitalWrite(CHUTE, LOW);
delay(100);
digitalWrite(CHUTE, HIGH);
delay(900);
}
}


// calibrar offset do x, y e z
void compassCalibrate(void)
{
  
  Serial.println("calibrando o compasso");
  MagnetometerScaled valueMax = {0, 0, 0};
  MagnetometerScaled valueMin = {0, 0, 0};

  //calcular offset
  

  Serial.println("por favor gire o robô");
  int xcount = 0;
  int ycount = 0;
  int zcount = 0;
  boolean xZero = false;
  boolean yZero = false;
  boolean zZero = false;
  MagnetometerScaled value;
  while (xcount < 3 || ycount < 3 || zcount < 3) {
    value = compass.readScaledAxis();
    if ((fabs(value.XAxis) > 600) || (fabs(value.YAxis) > 600) || (fabs(value.ZAxis) > 600)) {
      continue;
    }
    
    if (valueMin.XAxis > value.XAxis) {
      valueMin.XAxis = value.XAxis;
    } else if (valueMax.XAxis < value.XAxis) {
      valueMax.XAxis = value.XAxis;
    }
    
    if (valueMin.YAxis > value.YAxis) {
      valueMin.YAxis = value.YAxis;
    } else if (valueMax.YAxis < value.YAxis) {
      valueMax.YAxis = value.YAxis;
    }
    
    if (valueMin.ZAxis > value.ZAxis) {
      valueMin.ZAxis = value.ZAxis;
    } else if (valueMax.ZAxis < value.ZAxis) {
      valueMax.ZAxis = value.ZAxis;
    }
    
    
    if (xZero) {
      if (fabs(value.XAxis) > 50) {
        xZero = false;
        xcount++;
      }
    } else {
      if (fabs(value.XAxis) < 40) {
        xZero = true;
      }
    }
    
    if (yZero) {
      if (fabs(value.YAxis) > 50) {
        yZero = false;
        ycount++;
      }
    } else {
      if (fabs(value.YAxis) < 40) {
        yZero = true;
      }
    }
    
    if (zZero) {
      if (fabs(value.ZAxis) > 50) {
        zZero = false;
        zcount++;
      }
    } else {
      if (fabs(value.ZAxis) < 40) {
        zZero = true;
      }
    }
    
    delay(30);
  }
  
  valueOffset.XAxis = (valueMax.XAxis + valueMin.XAxis) / 2;
  valueOffset.YAxis = (valueMax.YAxis + valueMin.YAxis) / 2;
  valueOffset.ZAxis = (valueMax.ZAxis + valueMin.ZAxis) / 2;
#if 0 
  Serial << "max: " << valueMax.XAxis << '\t' << valueMax.YAxis << '\t' << valueMax.ZAxis << endl;
  Serial << "min: " << valueMin.XAxis << '\t' << valueMin.YAxis << '\t' << valueMin.ZAxis << endl;
  Serial << "offset: " << valueOffset.XAxis << '\t' << valueOffset.YAxis << '\t' << valueOffset.ZAxis << endl;
  
  Serial << "<<<<" << endl;
#endif  
  Serial.print("max: ");
  Serial.print(valueMax.XAxis);
  Serial.print(valueMax.YAxis);
  Serial.println(valueMax.ZAxis);
  Serial.print("min: ");
  Serial.print(valueMin.XAxis);
  Serial.print(valueMin.YAxis);
  Serial.println(valueMin.ZAxis);
  Serial.print("offset: ");
  Serial.print(valueOffset.XAxis);
  Serial.print(valueOffset.YAxis);
  Serial.println(valueOffset.ZAxis);
}

