// Motor pins
int motor1Pin1 = 2;  // IN1 for Motor A
int motor1Pin2 = 3;  // IN2 for Motor A
int motor2Pin1 = 4;  // IN3 for Motor B
int motor2Pin2 = 5;  // IN4 for Motor B

// Joystick pins
int joyX = A0;  // Joystick X-axis (horizontal)
int joyY = A1;  // Joystick Y-axis (vertical)
int joyButton = 6; // Joystick button (SW) pin

// Joystick range
int joyXValue;
int joyYValue;
bool buttonPressed = false;
bool motorsOn = false;

void setup() {
  // Set motor control pins as output
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Set button pin as input with internal pull-up resistor
  pinMode(joyButton, INPUT_PULLUP);  

  // Start serial communication for debugging
  Serial.begin(9600);
}

void loop() {
  // Read joystick X and Y values (range 0-1023)
  joyXValue = analogRead(joyX);
  joyYValue = analogRead(joyY);

  // Read the state of the joystick button
  buttonPressed = digitalRead(joyButton) == LOW; // Button pressed when LOW (active low)

  // Debugging: Print joystick values and button state to the serial monitor
  Serial.print("X: ");
  Serial.print(joyXValue);
  Serial.print(" Y: ");
  Serial.print(joyYValue);
  Serial.print(" Button: ");
  Serial.println(buttonPressed ? "Pressed" : "Not Pressed");

  // Turn on the motors when button is pressed
  if (buttonPressed) {
    motorsOn = true;
  }

  // If the motors are turned on and button is not pressed, turn off the motors
  if (!buttonPressed) {
    motorsOn = false;
    // Stop both motors when button is not pressed
    digitalWrite(motor1Pin1, LOW);
    digitalWrite(motor1Pin2, LOW);
    digitalWrite(motor2Pin1, LOW);
    digitalWrite(motor2Pin2, LOW);
  }

  // If motors are on, move the motors according to the joystick
  if (motorsOn) {
    // Map the joystick values to motor control (0-255 for motor speed)
    int motorSpeedX = map(joyXValue, 0, 1023, -255, 255);
    int motorSpeedY = map(joyYValue, 0, 1023, -255, 255);

    // Control Motor A (Motor 1) based on X-axis
    if (motorSpeedX > 0) {
      // Move forward
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
    } else if (motorSpeedX < 0) {
      // Move backward
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
    } else {
      // Stop Motor A
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, LOW);
    }

    // Control Motor B (Motor 2) based on Y-axis
    if (motorSpeedY > 0) {
      // Move forward
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
    } else if (motorSpeedY < 0) {
      // Move backward
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, HIGH);
    } else {
      // Stop Motor B
      digitalWrite(motor2Pin1, LOW);
      digitalWrite(motor2Pin2, LOW);
    }
  }

  // Delay for smoother control (optional)
  delay(100);
}
