# Railway Barrier Control System

This project is a Railway Barrier Control System that automates and manually controls railway gates, logs operator actions, and sends alerts through email and SMS. It includes an Arduino-based hardware setup and a Tkinter-based Python GUI.

## Features

- **Automatic Mode:** Closes and opens gates based on IR sensors detecting train entry and exit.
- **Manual Control:** Operators can manually open or close gates via the GUI.
- **Operator Validation:** Validates operator credentials from an Excel sheet.
- **Alert System:** Sends email and SMS notifications for gate operations and failures.
- **Logging:** Logs all events with timestamps in a CSV file.

## Hardware Requirements

- Arduino Uno
- 2 Servo Motors (for gate control)
- 2 IR Sensors (train detection)
- LEDs (Red/Green for gate status)
- Buzzer (audible alerts)
- Push Buttons (optional for manual hardware control)
- Jumper Wires

## Software Requirements

- Python 3
- Tkinter (GUI)
- Pandas (Excel handling)
- smtplib (Email notifications)
- Twilio (SMS notifications)
- Arduino IDE (for uploading the sketch)

## Installation & Setup

1. **Arduino:**
   - Upload the provided Arduino code to your Arduino Uno.
   - Connect sensors, LEDs, and servo motors as described in the code comments.

2. **Python GUI:**
   - Install required libraries:
     ```bash
     pip install pandas twilio pyserial openpyxl
     ```
   - Place your operator list in `operators.xlsx`.
   - Run the GUI:
     ```bash
     python railway_barrier_gui.py
     ```

3. **Email & SMS Configuration:**
   - Update the `SENDER_EMAIL`, `SENDER_PASSWORD`, and Twilio credentials in the Python code.
   - Ensure less secure app access is enabled for your email.

## Usage

1. Launch the GUI.
2. Enter the operator name and ID (up to 3 attempts).
3. Monitor train status, gate position, and connection status.
4. Manually control gates if needed with the provided buttons.

## Safety Measures

- **Buzzer Alert:** Sounds during gate closure.
- **Red Blinking LED:** Indicates gate is closed.
- **Manual Override:** Allows switching from automatic to manual mode.

## File Structure
```
├── railway_barrier_gui.py        # Main GUI script
├── railway_gate_controller.ino   # Arduino sketch
├── operators.xlsx                # Operator credentials
├── log_output_<timestamp>.csv    # Event logs
└── README.md                     # Documentation
```

## Future Improvements

- Add LCD display for on-site messages.
- Integrate cloud logging for remote monitoring.
- Add more sensors for multi-track detection.

## License

This project is open-source under the MIT License.

---

Let me know if you’d like me to refine this or add more sections! 🚀

