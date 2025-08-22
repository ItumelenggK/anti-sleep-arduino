# Anti-Sleep Glasses

## Project Overview
Anti-Sleep Glasses detect drowsiness using sensors and provide alerts. The system includes:

- **Arduino Uno** (sensors & data collection)  
- **HC-05 Bluetooth** (communication)  
- **Flask AI Emulator** (software analysis)  
- **Mobile app** (optional / future, for alerts and visualization)

---

## System Components

### Arduino Board
- Acts as the data collection unit.  
- Receives real-time input from the **MPU6050** (motion sensor) and **IR sensor**.  
- Processes the raw data and sends it via Bluetooth using the **HC-05 module**.

### Bluetooth Communication (HC-05)
- Sends data from Arduino to your laptop (AI emulator).  
- Data is transmitted as a simple text stream (JSON or CSV).

### Flask App on Laptop (AI Emulator)
- Receives incoming data (live from HC-05 or dummy data during testing).  
- Analyses it using AI logic to detect drowsiness.  
- If drowsiness is detected, triggers a simulated alert response.

### Mobile App (Optional / Future)
- Receives alerts.  
- Displays awake/sleepy state.  
- May also show graphs and stats (stretch goal).

---

## Software Setup (Python & Flask)

- Installed Python 3.12 and Flask to create a web-based emulator.  
- Developed Flask endpoints (`/` and `/dummy_sensor`) to test and return dummy sensor data.  
- Tested locally by running Flask and viewing JSON responses in a browser.

---

## Hardware Setup (Arduino IDE)

- Installed **Arduino IDE** and configured it for the Arduino Uno board.  
- Developed Arduino code to read sensor values from:  
  - **MPU6050 Accelerometer & Gyroscope**  
  - **IR sensor** (eye open/closed detection)  
- Used **HC-05 Bluetooth module** to transmit data wirelessly to PC/mobile.

---

## How Arduino IDE Fits In

- Arduino IDE writes and uploads firmware code to the microcontroller:  
  - Reads raw sensor data (MPU6050 + IR).  
  - Sends data via Bluetooth.  
- Real sensor data will eventually replace dummy sensor data in the Flask app.  

| Step | Tool / Component | Purpose |
|------|----------------|---------|
| Code sensor reading logic | Arduino IDE | Reads data from MPU6050 and IR sensors |
| Send sensor data | HC-05 Bluetooth module | Wireless transmission of sensor data to PC/mobile |
| Simulate data (software) | Flask Emulator | Simulate sensor data and drowsiness prediction |
| Receive real data (future) | Flask / Mobile App | Process real-time data, analyse, alert if drowsy |

---

## Instructions for Arduino IDE

1. Download and install Arduino IDE from [arduino.cc](https://www.arduino.cc/).  
2. Connect Arduino board via USB.  
3. Install necessary libraries (e.g., MPU6050 library).  
4. Write or import code to:  
   - Initialize sensors  
   - Continuously read sensor values  
   - Send data via Serial or Bluetooth  
5. Upload code to Arduino board.  
6. Test sensor readings using **Serial Monitor**.  
7. Ensure HC-05 is configured and paired with PC/mobile for wireless transmission.

---

## Next Steps

- Replace Flask dummy sensor endpoint with real data from Arduino via Bluetooth.  
- Build communication interface between Arduino (hardware) and Flask app (software).  
- Add alerts, logging, and visualizations for drowsiness detection.

---

## Authors / Contributors
- Your name / team members here  

---

## References
- [Arduino Official Website](https://www.arduino.cc/)  
- [Flask Documentation](https://flask.palletsprojects.com/)  
- [Adafruit MPU6050 Library](https://github.com/adafruit/Adafruit_MPU6050)
