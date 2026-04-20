/*
  Serial Event example

  When new serial data arrives, this sketch adds it to a String.
  When a newline is received, the loop prints the string and clears it.

  A good test for this is to try it with a GPS receiver that sends out
  NMEA 0183 sentences.

  NOTE: The serialEvent() feature is not available on the Leonardo, Micro, or
  other ATmega32U4 based boards.

  created 9 May 2011
  by Tom Igoe

  This example code is in the public domain.

  https://docs.arduino.cc/built-in-examples/communication/SerialEvent/
*/

String inputString = "";      // a String to hold incoming data
bool stringComplete = false;  // whether the string is complete

const int FRONT_LEFT_IN1 = 35;
const int FRONT_LEFT_IN2 = 37;
const int FRONT_LEFT_SPEED = 39;

const int FRONT_RIGHT_IN1 = 41;
const int FRONT_RIGHT_IN2 = 43;
const int FRONT_RIGHT_SPEED = 45;

const int BACK_LEFT_IN1 = 47;
const int BACK_LEFT_IN2 = 49;
const int BACK_LEFT_SPEED = 51;

const int BACK_RIGHT_IN1 = 34;
const int BACK_RIGHT_IN2 = 36;
const int BACK_RIGHT_SPEED = 38;

const bool magnetState = false;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  Serial1.begin(9600);
  // reserve 200 bytes for the inputString:
  pinMode(FRONT_LEFT_IN1, OUTPUT);
  pinMode(FRONT_LEFT_IN2, OUTPUT);
  pinMode(FRONT_LEFT_SPEED, OUTPUT);

  pinMode(FRONT_RIGHT_IN1, OUTPUT);
  pinMode(FRONT_RIGHT_IN2, OUTPUT);
  pinMode(FRONT_RIGHTT_SPEED, OUTPUT);

  pinMode(BACK_LEFT_IN1, OUTPUT);
  pinMode(BACK_LEFT_IN2, OUTPUT);
  pinMode(BACK_LEFT_SPEED, OUTPUT);
  
  pinMode(BACK_RIGHT_IN1, OUTPUT);
  pinMode(BACK_RIGHT_IN2, OUTPUT);
  pinMode(BACK_RIGHT_SPEED, OUTPUT);


  digitalWrite(FRONT_LEFT_IN1, LOW);
  digitalWrite(FRONT_LEFT_IN2, LOW);
  analogWrite(FRONT_LEFT_SPEED, 0);  //0-255

  digitalWrite(FRONT_RIGHT_IN1, LOW);
  digitalWrite(FRONT_RIGHT_IN2, LOW);
  analogWrite(FRONT_RIGHT_SPEED, 0);

  digitalWrite(BACK_LEFT_IN1, LOW);
  digitalWrite(BACK_LEFT_IN2, LOW);
  analogWrite(BACK_LEFT_SPEED, 0);

  digitalWrite(BACK_RIGHT_IN1, LOW);
  digitalWrite(BACK_RIGHT_IN2, LOW);
  analogWrite(BACK_RIGHT_SPEED, 0);

  inputString.reserve(200);
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);//debug print
    if(inputString.startsWith("LJ")){  //LJ,123,67\n
      //parse data to get x an y values


    }
    else if (inputString == "mD\n"){
      //I think this should be depressed until you press it again instead of holding it
      //Stuff
      if(magnetState == false){
        magnetState = true;
      } else {
        magnetState = false;
      }
      
      if (magnetState == true){
        digitalWrite(magnetPin, HIGH);
      } else {
        digitalWrite(magnetPin, LOW);
      }
      

    }
    //else if button is pressed

    else if (inputString == "lD\n"){

    }
    //else if button2 is pressed

    else if (inputString == "lU\n")
    //else if button2 isn't pressed

    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

/*
  SerialEvent occurs whenever a new data comes in the hardware serial RX. This
  routine is run between each time loop() runs, so using delay inside loop can
  delay response. Multiple bytes of data may be available.
*/
void serialEvent1() {
  while (Serial1.available()) {
    // get the new byte:
    char inChar = (char)Serial1.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
