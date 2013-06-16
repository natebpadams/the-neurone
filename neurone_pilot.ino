// THE NEURONE PILOT PROJECT CODE VERSION 0.1 DATE 25APRIL 2013
// MUCH THANKS TO THE FOLLOWING WEBSITES FOR RELEASING THEIR CODE
// http://www.treehouseprojects.ca/ultrasonictutorial/
// AND 
// http://arduino.cc/forum/index.php/topic,12004.0.html
// THIS CODE IS INTENDED FOR EDUCATIONAL PURPOSES ONLY AND IS FULL OF BUGS
// FOR MORE INFORMATION VISIT http://www.furnacepark.org/neurone


// This part of the code introduces the various inputs and output on the arduino


const int pingPin = 2;                 //trigger pin connected to pin 11
int inPin = 3;                         //echo pin connected to pin 10
int safeZone = 5;                      //Safe zone in centimeters

int value, value2;                      //some variables in terms on how bright LEDs wil be
int ledpin = 9;                         // purple light connected to digital pin 9
int ledpin2 = 6;                        // while light connected to digital pin 6
long time=0;                            // initial value for time

int periode = 1000;                     // how fast the fade is on the LEDs
int displace = 500;                     // an offset for the fade so they don't happen at the same time

void setup() 
{ 
  // initialize serial communication so we can monitor the distance sensor remotely
  Serial.begin(9600); 
} 

void loop() 
{ 
  
  long duration, cm;   // a 32 bit variable
  
  pinMode(pingPin, OUTPUT); //initialise trigger pin
  
  //sending the signal, starting with LOW for a clean signal
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);
  
   //setting up the input pin, and receiving the duration in
  //microseconds for the sound to bounce off the object infront 
  
  pinMode(inPin, INPUT);
  duration = pulseIn(inPin, HIGH);
  
   // convert the time into a distance
  cm = microsecondsToCentimeters(duration);
  
  //printing the current readings to ther serial display
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();

  //checking if anything is within the safezone, if not, keep
  //green LED on if safezone violated, activate red LED instead
  if (cm > safeZone)
  {
      time = millis();
      value = 128+127*cos(2*PI/periode*time);
      value2 = 128+127*cos(2*PI/periode*(displace-time));
      analogWrite(ledpin, value);           // sets the value (range from 0 to 255) 
      analogWrite(ledpin2, 0);           // sets the value (range from 0 to 255) v
  }
  else
  {
      time = millis();
      value = 128+127*cos(2*PI/periode*time);
      value2 = 128+127*cos(2*PI/periode*(displace-time));
      analogWrite(ledpin, value);           // sets the value (range from 0 to 255) 
      analogWrite(ledpin2, value2);           // sets the value (range from 0 to 255) 
  }
 
  delay(50); 
 
}

long microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}
