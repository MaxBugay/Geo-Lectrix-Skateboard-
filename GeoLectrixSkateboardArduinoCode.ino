/*
*  This code is in the public domain.
*  (Do whatever you want with it.)
*/

// Need the Servo library
#include <Servo.h>

// This is our motor.
Servo myMotor;

// This is the final output
// written to the motor.
String incomingString;
String speedCon;
String receivedMsg;
int speedVal;
int leftLED = 13;
int rightLED = 12;
// Set everything up
void setup()
{
  pinMode(leftLED, OUTPUT);
  pinMode(rightLED, OUTPUT);
  // Put the motor to Arduino pin #9
  myMotor.attach(9);

  // Required for I/O from Serial monitor
  Serial.begin(9600);
  // Print a startup message
  Serial.println("initializing");
}


void loop()
{
  
  // If there is incoming value
  if(Serial.available() > 0)
  {
    // read the value
    char ch = Serial.read();
    
    /*
    *  If ch isn't a newline
    *  (linefeed) character,
    *  we will add the character
    *  to the incomingString
    */
    if (ch != 10){
      // Print out the value received
      // so that we can see what is
      // happening
      Serial.print("I have received: ");
      Serial.print(ch, DEC);
      Serial.print('\n');
      
      // Add the character to
      // the incomingString
      receivedMsg += ch;
      Serial.print(receivedMsg);
    }
    if (receivedMsg == "start") {
        Serial.write("Success");
        incomingString = "100";
        speedVal = 100;
        receivedMsg = "";
    }
    else if (receivedMsg == "on"){
      Serial.write("Success");
      incomingString = "10";
      receivedMsg = "";
      speedVal = 90;
    }
    else if (receivedMsg == "stop") {
      Serial.write("Success");
        incomingString = "90";
        speedVal = 90;
        receivedMsg = "";
    }
    else if (receivedMsg == "off"){
      Serial.write("Success");
        incomingString = "95";
        speedVal = 90;
        receivedMsg = "";
    }
    else if (receivedMsg == "accel") {
      Serial.write("Success");
      speedCon = "2";
      receivedMsg = "";
    }
    else if (receivedMsg == "decel") {
      Serial.write("Success");
      speedCon = "1";
      receivedMsg = "";
    }
    else if (receivedMsg == "left") {
      Serial.write("Success");
      for (int i = 0; i < 6; i++) {
        digitalWrite(12, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(50);                       // wait for a second
        digitalWrite(12, LOW);    // turn the LED off by making the voltage LOW
        delay(50); 
      }
      incomingString = "";
      receivedMsg = "";
    }
    else if (receivedMsg == "right") {
      Serial.write("Success");
      for (int i = 0; i < 6; i++) {
        digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
        delay(50);                       // wait for a second
        digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
        delay(50); 
      }
      incomingString = "";
      receivedMsg = "";
    }
    // received a newline (linefeed) character
    // this means we are done making a string
    if (incomingString.toInt() >= 85 || incomingString.toInt() == 10)
    {
      // print the incoming string
      Serial.println("I am printing the entire string");
      Serial.println(incomingString);

      // Convert the string to an integer
      int val = incomingString.toInt();
    
      // print the integer
      Serial.println("Printing the value: ");
      Serial.println(val);
    
      /*
      *  We only want to write an integer between
      *  0 and 180 to the motor. 
      */
      if (val > -1 && val < 181)
     {
       // Print confirmation that the
       // value is between 0 and 180
       Serial.println("Value is between 0 and 180");
       // Write to Servo
       myMotor.write(val);
     }
     // The value is not between 0 and 180.
     // We do not want write this value to
     // the motor.
     else
     {
       Serial.println("Value is NOT between 0 and 180");
      
       // IT'S a TRAP!
       Serial.println("Error with the input");
     }
    
      // Reset the value of the incomingString
      incomingString = "";
    }
    else if ((speedCon.toInt() == 2 || speedCon.toInt() == 1) && speedVal != 0 && speedVal <= 120 && speedVal >= 100) {
      Serial.println("speedVal = ");
      Serial.println(speedVal);
      Serial.println('\n');
      if (speedCon.toInt() == 2) {
        myMotor.write(speedVal + 2);
        speedVal += 2;
        speedCon = "";
        incomingString = "";
      }
      else {
        myMotor.write(speedVal - 2);
        speedVal -= 2;
        speedCon = "";
        incomingString = "";
      }
    }
  }

}
