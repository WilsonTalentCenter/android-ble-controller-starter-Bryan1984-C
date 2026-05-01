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

const byte FRONT_LEFT_IN1 = 31;
const byte FRONT_LEFT_IN2 = 32;
const byte FRONT_LEFT_SPEED = 10;

const byte FRONT_RIGHT_IN1 = 33;
const byte FRONT_RIGHT_IN2 = 22;
const byte FRONT_RIGHT_SPEED = 8;

const byte BACK_LEFT_IN1 = 30;
const byte BACK_LEFT_IN2 = 48;
const byte BACK_LEFT_SPEED = 11;

const byte BACK_RIGHT_IN1 = 28;
const byte BACK_RIGHT_IN2 = 29;
const byte BACK_RIGHT_SPEED = 12;

bool magnetState = false;
byte magnetPin = 9;

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
  pinMode(FRONT_RIGHT_SPEED, OUTPUT);

  pinMode(BACK_LEFT_IN1, OUTPUT);
  pinMode(BACK_LEFT_IN2, OUTPUT);
  pinMode(BACK_LEFT_SPEED, OUTPUT);
  
  pinMode(BACK_RIGHT_IN1, OUTPUT);
  pinMode(BACK_RIGHT_IN2, OUTPUT);
  pinMode(BACK_RIGHT_SPEED, OUTPUT);

  pinMode(magnetPin, OUTPUT);


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

  // new 5.5v output pin
  pinMode(53, OUTPUT);
  digitalWrite(53, HIGH);


  inputString.reserve(200);
}

int leftSpeed = 0;
int rightSpeed = 0;

void loop() {

  // print the string when a newline arrives:
  if (stringComplete) {
    // Serial.println(inputString);//debug print
    if(inputString.startsWith("RJ")){ 
    // Example string: "RJ,128,255"
    // Find the commas to split the string
    int firstComma = inputString.indexOf(',');
    int secondComma = inputString.indexOf(',', firstComma + 1);
    
      if (firstComma != -1 && secondComma != -1) {
          int xVal = inputString.substring(firstComma + 1, secondComma).toInt();
          int yVal = inputString.substring(secondComma + 1).toInt();

          // Convert X/Y to motor speeds (Simple Tank Drive Example)
          // Adjust these ranges based on your controller's output (usually 0-255)
          leftSpeed = yVal*2; 
      }
  } else if(inputString.startsWith("LJ")) {
    int firstComma = inputString.indexOf(',');
    int secondComma = inputString.indexOf(',', firstComma + 1);
    if (firstComma != -1 && secondComma != -1) {
          int xVal = inputString.substring(firstComma + 1, secondComma).toInt();
          int yVal = inputString.substring(secondComma + 1).toInt();

          rightSpeed = yVal*2;
      }
  }


  else if (inputString.startsWith("mD")){
      magnetState = !magnetState; // Toggle state
      digitalWrite(magnetPin, magnetState ? HIGH : LOW);
      digitalWrite(magnetPin, magnetState ? HIGH : LOW);
      digitalWrite(LED_BUILTIN, magnetState ? HIGH : LOW);
    }

    // clear the string:
    inputString = "";
    stringComplete = false;
  }

  moveRobot(leftSpeed, rightSpeed); 

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

void moveRobot(int leftSpeed, int rightSpeed) {
  // Front Left
  digitalWrite(FRONT_LEFT_IN1, leftSpeed > 0 ? HIGH : LOW);
  digitalWrite(FRONT_LEFT_IN2, leftSpeed > 0 ? LOW : HIGH);
  analogWrite(FRONT_LEFT_SPEED, abs(leftSpeed));
  Serial.print(abs(leftSpeed));

  // Front Right
  digitalWrite(FRONT_RIGHT_IN1, rightSpeed > 0 ? HIGH : LOW);
  digitalWrite(FRONT_RIGHT_IN2, rightSpeed > 0 ? LOW : HIGH);
  analogWrite(FRONT_RIGHT_SPEED, abs(rightSpeed));

  // BACK_LEFT
  digitalWrite(BACK_LEFT_IN1, leftSpeed > 0 ? HIGH : LOW);
  digitalWrite(BACK_LEFT_IN2, leftSpeed > 0 ? LOW : HIGH);
  analogWrite(BACK_LEFT_SPEED, abs(leftSpeed));

  // BACK_RIGHT
  digitalWrite(BACK_RIGHT_IN1, leftSpeed > 0 ? HIGH : LOW);
  digitalWrite(BACK_RIGHT_IN2, leftSpeed > 0 ? LOW : HIGH);
  analogWrite(BACK_RIGHT_SPEED, abs(rightSpeed));
}
