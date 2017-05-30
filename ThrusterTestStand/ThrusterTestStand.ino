// Use Arduino servo library to control the ESC speed controller
#include <Servo.h>

/*********************
 * TEST & CIRCUIT PARAMETERS
 *********************/

// Test parameters
int NUM_TEST_POINTS = 5;
int STABILIZATION_DELAY = 2000; // milliseconds

// Arduino parameters
float ARDUINO_VOLT_PER_DIV = (5.0/1023.0);
int START_SWITCH_PIN = 2;
int LOAD_CELL_ANALOG_PIN = 0;

// Load cell parameters
float LOAD_CELL_LB_PER_VOLT = (50.0 / 4.0);
float LOAD_CELL_VOLT_OFFSET = 0.5;

// Thruster PWM values
int STOP = 1500;
int MAX_PWM = 1900;
int MIN_PWM = 1100;


/*********************
 * VARIABLES
 *********************/

// Serial variables
int SERIAL_BAUD_RATE = 9600;

int currentPWM = STOP;
int deltaPWM;
bool forwardThrust = true;
int testRunning = false;

// Function prototypes
int16_t valid(int16_t pwm);

void setup() {
  Serial.begin(SERIAL_BAUD_RATE);
  deltaPWM = (MAX_PWM - STOP) / NUM_TEST_POINTS;

  // Setup start switch
  pinMode(START_SWITCH_PIN, INPUT);
}

void loop(){
  // Check for running switch
  if (digitalRead(START_SWITCH_PIN)) {
    testRunning = true;
  } else {
    // Send STOP to thruster
    
    // Reset the test
    testRunning = false;
    forwardThrust = true;
    currentPWM = STOP;
  }
     
  if (testRunning) {
    // Run thruster

    // Delay for force to stabilize
    delay(STABILIZATION_DELAY);
    
    // Read force
    
    int senseValue = analogRead(LOAD_CELL_ANALOG_PIN);
    
    // Kill thruster
    
    // Log PWM and force
    
    float loadCellVoltage = senseValue * ARDUINO_VOLT_PER_DIV;
    float loadCellForce = (loadCellVoltage - LOAD_CELL_VOLT_OFFSET) * LOAD_CELL_LB_PER_VOLT;
    Serial.println(currentPWM);
    Serial.println(loadCellForce);
    Serial.println(); 

    // Delay for stabilization
    delay(STABILIZATION_DELAY);
    
    // Move to next PWM
    if (currentPWM >= MAX_PWM) {
      forwardThrust = false;
      currentPWM = STOP;
    } else if (currentPWM <= MIN_PWM) {
      currentPWM = STOP;
      testRunning = false;
    } else if (forwardThrust) {
      currentPWM += deltaPWM;
    } else {
      currentPWM -= deltaPWM;
    } 
  }
}

// Ensure MIN_PWM <= pwm <= MAX_PWM
int16_t valid(int16_t pwm)
{
  pwm = pwm > MAX_PWM ? MAX_PWM : pwm;
  pwm = pwm < MIN_PWM ? MIN_PWM : pwm;
  return pwm;
}


