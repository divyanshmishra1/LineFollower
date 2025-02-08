
# LineFollower
Making a line follower robot using Arduino Nano

# Line Following Robot 🚗

This project is an Arduino-based **line-following robot** that uses **PID control** to follow a black line on a white surface. It utilizes **five IR sensors** to detect the line and adjust motor speeds accordingly for smooth navigation.

## 📜 Features
- Uses **5 IR sensors** (KTIR0711S) for precise line detection.
- Implements **PID-based control** for stable movement.
- Controls two DC motors with an **L298N motor driver**.
- Supports a **push-button start/stop mechanism**.

## 🔧 Components Used
- **Arduino Nano** (or any compatible board)
- **L298N Motor Driver**
- **KTIR0711S IR Sensors** (5x)
- **12V DC Motors** (Pololu HPCB)
- **12V Battery Pack**
- **Push Button & LED**
- **Wheels & Chassis**

## 📁 Project Structure
```
line_follower/
│── 📂 src/                 # Source code directory
│   ├── line_follower.ino   # Arduino code
│── 📂 images/              # Images and schematics
│── 📂 docs/                # Documentation
│   ├── SCHEMATICS.png      # Circuit diagram
│   ├── components.md       # List of components
│── .gitignore              # Ignore unnecessary files
│── LICENSE                 # License file (MIT recommended)
│── README.md               # Project overview
```

## ⚙️ Circuit Diagram

                  +12V Battery Pack
                        │
            ┌───────────┴───────────┐
            │                       │
          (M1)                     (M2)  <-- DC Motors (Pololu HPCB)
            │                       │
      ┌─────┴─────┐           ┌─────┴─────┐
      │   L298N   │           │   L298N   │  <-- Motor Driver Module
      │ Motor A   │           │ Motor B   │
      │  (enA) ───┼── D9       │  (enB) ───┼── D3       <-- PWM Speed Control
      │  (IN1) ───┼── D6       │  (IN3) ───┼── D5       <-- Direction Control
      │  (IN2) ───┼── D4       │  (IN4) ───┼── D2
      └───────────┘           └───────────┘
               │                      │
               │                      │
               └─── GND (Common Ground) ───┐
                                           │
    ┌─────────────────────────────────────┴─────────────────────────────────────┐
    │                            Arduino Nano (ATmega328P)                       │
    │  ┌──────────────────────────────────────────────────────────────────┐       │
    │  │ A0 ─── S1 (Leftmost IR Sensor)   D12 ─── Push Button              │       │
    │  │ A1 ─── S2                        D13 ─── LED (Indicator)          │       │
    │  │ A2 ─── S3 (Center IR Sensor)                                    5V ├─── IR Sensors (5x KTIR0711S)
    │  │ A6 ─── S4                                                     GND ├─── Motor Driver & Sensors
    │  │ A7 ─── S5 (Rightmost IR Sensor)                              VIN ├─── 12V Power Input
    │  └──────────────────────────────────────────────────────────────────┘       │
    └────────────────────────────────────────────────────────────────────────────┘




## 🚀 Setup & Usage
1. **Assemble the hardware** as per the circuit diagram.
2. **Upload** the code from `src/line_follower.ino` to the Arduino.
3. **Power on** the robot and place it on the track.
4. **Press the button** to start following the line.

## 🖥️ Code Overview
The robot reads IR sensor data, converts it into a position value, and adjusts motor speeds using **PID control**.

### Key Functions:
- **`Sensor_reading()`** → Reads IR sensor values.
- **`PID_LINE_FOLLOW()`** → Implements PID-based motor control.
- **`motor(int a, int b)`** → Controls motor speed and direction.

## 🏆 Achievements
This project was developed by out team **Track Titans** under the **IRIS Robotics Club** at IIIT Dharwad. It was presented at **Robolympics 2025**, hosted by **Indian Institute of Science (IISc) Bangalore**, where our team secured **3rd place at the national level**.
## 📜 License
This project is licensed under the **MIT License**. Feel free to modify and share!

---

