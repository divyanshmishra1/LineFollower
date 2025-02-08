// Motor Driver Pin Definitions
#define IN1 6
#define IN2 5
#define IN3 4
#define IN4 2
#define enA 9
#define enB 3

// Line Following Sensor Variables
int s[6], total = 0, sensor_position = 0;
const int threshold = 531;  // Set threshold based on calibration
const int set_point = 3;
float avg;
int position[6] = { 1, 2, 3, 4, 5 };

// Push Button and LED
const int button_pin = 12;
const int led = 13;
bool button_pin_state = false;

void setup() {
    // Set motor driver pins as output
    pinMode(IN1, OUTPUT);
    pinMode(IN2, OUTPUT);
    pinMode(IN3, OUTPUT);
    pinMode(IN4, OUTPUT);

    // Set button pin as input with pull-up resistor
    pinMode(button_pin, INPUT_PULLUP);

    // LED as output
    pinMode(led, OUTPUT);

    // Start Serial Communication
    Serial.begin(9600);
}

void loop() {
    button_pin_state = digitalRead(button_pin);
    display_value();

    // When the button is pressed, start following the line
    while (button_pin_state != HIGH) {
        blinkLED(3);  // Blink LED 3 times before starting
        PID_LINE_FOLLOW();
    }
}

// Read sensor values and calculate position
void Sensor_reading() {
    sensor_position = 0;
    total = 0;

    for (byte i = 0; i < 5; i++) {  
        // Read sensor data from A0, A1, A2, A6, A7
        s[i] = (i > 2) ? analogRead(i + 3) : analogRead(i);
        s[i] = (s[i] > threshold) ? 1 : 0;  // Convert analog to digital

        sensor_position += s[i] * position[i];
        total += s[i];
    }

    if (total > 0) avg = sensor_position / total;
}

// Line Following using PID Control
void PID_LINE_FOLLOW() {
    const int kp = 50, kd = 500, base_speed = 200, turn_speed = 100;
    int PID_Value, P, D;
    float error, previous_error = 0;
    int left_motor_speed, right_motor_speed;
    char t;

    while (true) {
        Sensor_reading();
        error = set_point - avg;
        P = kp * error;
        D = kd * (error - previous_error);
        PID_Value = P + D;
        previous_error = error;

        // Adjust motor speeds
        right_motor_speed = base_speed - PID_Value;
        left_motor_speed = base_speed + PID_Value;
        motor(left_motor_speed, right_motor_speed);

        // Handle line loss scenarios
        Sensor_reading();
        if (total == 0) {  
            digitalWrite(led, HIGH);
            if (t != 's') {
                (t == 'r') ? motor(turn_speed, -turn_speed) : motor(-turn_speed, turn_speed);
                while (!s[2]) Sensor_reading();
                digitalWrite(led, LOW);
            }
        }

        // Detect turns
        if (s[4] && !s[0]) t = 'l';
        if (!s[4] && s[0]) t = 'r';

        // Stop if all sensors detect a line
        else if (total == 5) { 
            Sensor_reading();
            if (total == 5) {
                motor(0, 0);
                while (total == 5) Sensor_reading();
            } else if (total == 0) t = 's';
        }
    }
}

// Display sensor values in Serial Monitor
void display_value() {
    for (byte i = 0; i < 5; i++) {
        s[i] = (i > 2) ? analogRead(i + 3) : analogRead(i);
        Serial.print(String(s[i]) + " ");
    }
    Serial.println();
    delay(50);
}

// Motor Control Function
void motor(int left_speed, int right_speed) {
    // Set motor direction
    digitalWrite(IN3, left_speed > 0);
    digitalWrite(IN4, left_speed <= 0);
    digitalWrite(IN1, right_speed > 0);
    digitalWrite(IN2, right_speed <= 0);

    // Limit speed values
    left_speed = constrain(abs(left_speed), 0, 200);
    right_speed = constrain(abs(right_speed), 0, 200);

    // Apply speed to motors
    analogWrite(enB, left_speed);
    analogWrite(enA, right_speed);
}

// LED Blink Function
void blinkLED(int times) {
    for (int i = 0; i < times; ++i) {
        digitalWrite(led, HIGH);
        delay(100);
        digitalWrite(led, LOW);
        delay(100);
    }
}

