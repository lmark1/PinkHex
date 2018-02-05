
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

// Direction pin number
const int dirPin_forward = 2; 
const int dirPin_reverse = 13; 

// Motor enable pin constant
const int enablePin = 5;

// Speed regulator pins
const int MS1 = 6;
const int MS2 = 7;
const int MS3 = 8;

// Keyboard constants
const char action_forward = 'i';
const char action_stop = 'k';
const char action_backward = ',';
const char action_standup = 'w';
const char action_sitdown = 's';

// Define motor sets
int motor_set_1[3] = { 
    stepper_1, 
    stepper_4, 
    stepper_5 
  };
int motor_set_2[3] = { 
    stepper_2, 
    stepper_3, 
    stepper_6 
};
int motor_set_all[6] = {
    stepper_1,
    stepper_2,
    stepper_3,
    stepper_4,
    stepper_5,
    stepper_6
};

// Define motor revolution constant
int full_revolution_cycle = 800;

// Variables for recieving input via serial
char last_action = 'k'; // Initial value is k = stop
boolean newData = false;

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
   
  pinMode(dirPin_forward,OUTPUT);
  pinMode(dirPin_reverse,OUTPUT);
  
  pinMode(enablePin, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);

  // Enable motor
  digitalWrite(enablePin, LOW);

  // Speed - quarter step
  // MS1 - L, MS2 - H, MS3 - L
  digitalWrite(MS1, LOW);
  digitalWrite(MS2, HIGH);
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
  
  } else if (last_action == action_standup) {
    standUp();
  
  } else if (last_action == action_sitdown) {
    sitDown();
  }
  
  showNewData();
}

/**
 * Go backward once.
 */
void goBackward() {

  //Changes the rotations direction
  digitalWrite(dirPin_forward,LOW); 
  digitalWrite(dirPin_reverse,HIGH);
 
  runMotorsOnce(motor_set_1, 3, full_revolution_cycle);
  delay(150);
 
  runMotorsOnce(motor_set_2, 3, full_revolution_cycle);
  delay(150);
}


/**
 * Go forward once.
 */
void goForward() {

  // Enables the motor to move forward
  digitalWrite(dirPin_forward,HIGH); 
  digitalWrite(dirPin_reverse,LOW);
 
  runMotorsOnce(motor_set_1, 3, full_revolution_cycle);
  delay(150);
 
  runMotorsOnce(motor_set_2, 3, full_revolution_cycle);
  delay(150);
}

void standUp() {

  //Changes the rotations direction
  digitalWrite(dirPin_forward,LOW); 
  digitalWrite(dirPin_reverse,HIGH);
 
  // Do a quarter revolution forward
  runMotorsOnce(motor_set_all, 6, full_revolution_cycle / 4);
  Serial.println("Stand up - started.");
  
  // Reset action
  last_action = action_stop;
}

void sitDown() {

  //Changes the rotations direction
  digitalWrite(dirPin_forward,HIGH); 
  digitalWrite(dirPin_reverse,LOW);
 
  // Do a quarter revolution backward
  runMotorsOnce(motor_set_all, 6, full_revolution_cycle / 4);
  Serial.println("Sit down - started.");

  // Reset action
  last_action = action_stop;
}

/**
 * Recieve one char from serial port.
 */
void recieveOneChar() {
    if (Serial.available() > 0) {
        char temp_char = Serial.read();
        last_action = temp_char;       
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
 * motor_indices[] - int array with motor pin values
 * size_of_array - size of motor indices array
 * revolution_cycle - number of revolutions - 200 for full cycle
 */
void runMotorsOnce(
  int motor_indices[], 
  int size_of_array, 
  int revolution_cycle) {
  
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < revolution_cycle; x++) {
    
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