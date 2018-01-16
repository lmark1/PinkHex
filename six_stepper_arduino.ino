
/**
 * @author PinkHex - Batinovic, Markovic, Mikic
 */

// Stepper motor pins 
const int stepper_1 = 3; 
const int stepper_2 = 4;
const int stepper_3 = 9;
const int stepper_4 = 10;
const int stepper_5 = 11;
const int stepper_6 = 12;

// Direction pin numver
const int dirPin = 2; 

// Motor enable pin constant
const int enablePin = 5;

// Speed regulator pins
const int MS1 = 6;
const int MS2 = 7;
const int MS3 = 8;

// Variables for recieving input via serial
char last_action = 'k'; // Initial value is k = stop
boolean newData = false;

// Keyboard constants
const char action_forward = 'i';
const char action_stop = 'k';
const char action_backward = ',';

void setup() {

  Serial.begin(115200);
  Serial.println("<Arduino is ready>");
   
  // Sets the two pins as Outputs
  pinMode(stepper_1,OUTPUT);
  pinMode(stepper_2,OUTPUT);
  pinMode(stepper_3,OUTPUT);
  pinMode(stepper_4,OUTPUT);
  pinMode(stepper_5,OUTPUT);
  pinMode(stepper_6,OUTPUT);
   
  pinMode(dirPin,OUTPUT);
  pinMode(enablePin, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  // Enable motor
  digitalWrite(enablePin, LOW);

  // Speed - quarter step
  // MS1 - L, MS2 - H, MS3 - L
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, LOW);
  digitalWrite(MS3, LOW);
}

void loop() {

  recieveOneChar();

  // Check user input - do appropriate action
  if (last_action == action_stop) {
    // Do nothing... robot stops
    
  } else if (last_action == action_forward) {
     goForward();
  
  } else if (last_action == action_backward) {
    goBackward();
  }

  showNewData();
}

/**
 * Go backward once.
 */
void goBackward() {
  int motor_set_1[3] = { stepper_1, stepper_2, stepper_3 };
  int motor_set_2[3] = { stepper_4, stepper_5, stepper_6 };
  
  runBackwardOnce(motor_set_1, 3);
  delay(150);
  
  runBackwardOnce(motor_set_2, 3);
  delay(150);
}


/**
 * Go forward once.
 */
void goForward() {
  
  int motor_set_1[3] = { stepper_1, stepper_2, stepper_3 };
  int motor_set_2[3] = { stepper_4, stepper_5, stepper_6 };
  
  runForwardOnce(motor_set_1, 3);
  delay(150);
  
  runForwardOnce(motor_set_2, 3);
  delay(150);
}

/**
 * Recieve one char from serial port.
 */
void recieveOneChar() {
    if (Serial.available() > 0) {
        char temp_char = Serial.read();

        // Check if last recieved char is one of the available actions
        if (
          temp_char == action_forward || 
          temp_char == action_stop || 
          temp_char == action_backward) {
           
          last_action = temp_char;
        }
        
        newData = true;
    }
}

/**
 * Print out recieved character.
 */
char showNewData() {
    if (newData == true) {
        Serial.print("Robot action: ");
        Serial.println(last_action);
        newData = false;
    }
}

/**
 * Run forward selected motors.
 * 
 * @motor_indices[] - int array with motor pin values
 */
void runForwardOnce(int motor_indices[], int size_of_array) {
  
  // Enables the motor to move in a particular direction
  digitalWrite(dirPin,HIGH); 
  
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < 200; x++) {
    
    enableMotors(motor_indices, size_of_array);
    delayMicroseconds(500); 
    
    disableMotors(motor_indices, size_of_array);
    delayMicroseconds(500); 
  }
}


/**
 * Run backward selected motors.
 * 
 * @motor_indices[] - int array with motor pin values
 */
void runBackwardOnce(int motor_indices[], int size_of_array) {

  //Changes the rotations direction
  digitalWrite(dirPin,LOW); 
  
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < 200; x++) {
    
    enableMotors(motor_indices, size_of_array);
    delayMicroseconds(500);
    
    disableMotors(motor_indices, size_of_array);
    delayMicroseconds(500);
  }
}

/**
 * Put HIGH values on all given motor indices.
 * 
 * @motor_indices[] - int array with motor pin values
 */
void enableMotors(int motor_indices[], int size_of_array) {
  int i;
  
  for (i = 0; i < size_of_array; i++) {
    digitalWrite(motor_indices[i], HIGH);
  }
}

/**
 * Put LOW values on all given motor indices.
 * 
 * @motor_indices[] - int array with motor pin values
 */
void disableMotors(int motor_indices[], int size_of_array) {
  int i;
  
  for (i = 0; i < size_of_array; i++) {
    digitalWrite(motor_indices[i], LOW);
  }
}
