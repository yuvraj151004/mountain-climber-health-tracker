# Mountain Climber Health & Location Tracker ⛰️📡

An **Arduino-based wearable system** that monitors a climber’s **temperature, heartbeat, and GPS location** in real time.  
The device can send **emergency SMS alerts with live coordinates** using a GSM module.

---

## 🚀 Features
- Monitor **temperature & heartbeat** with sensors
- **GPS tracking** with Google Maps link
- **SOS button** for emergency help
- **SMS alerts** via GSM (SIM800L / SIM900)
- 16x2 **LCD display** for live readings

---

## 🛠️ Tech Stack
- **Microcontroller:** Arduino UNO  
- **Sensors:** Temperature sensor (A1), Heartbeat sensor (A0)  
- **Modules:** GPS, GSM (SIM800L/SIM900), LCD I2C  
- **Language:** C++ (Arduino IDE)  
- **Libraries:** TinyGPS, SoftwareSerial, Wire, LiquidCrystal_I2C  

---

## 📂 Repo Structure
- `firmware/` → Arduino sketch (`health_tracker.ino`)  
- `hardware/` → circuit diagram & components list  
- `docs/` → usage guide & setup instructions  
- `images/` → screenshots and demo images  

---

## 🔧 Setup Instructions
1. Install Arduino IDE and required libraries:
   - TinyGPS
   - SoftwareSerial
   - Wire
   - LiquidCrystal_I2C
2. Connect hardware according to `hardware/components_list.md`.  
3. Upload `firmware/health_tracker.ino` to Arduino.  
4. Insert SIM card into GSM module.  
5. Test by sending SMS `"LOCAL"` → you’ll get temperature, heartbeat, and GPS location.  

---

## 📸 Demo
![Demo Screenshot](images/demo1.jpg)  
*(Replace with your actual screenshot paths)*  

---

## 🎯 Future Improvements
- Cloud dashboard for real-time monitoring  
- Low-power optimization  
- Mobile app integration for tracking  
