# mountain-climber-health-tracker
Arduino-based wearable to monitor climber’s health and GPS location with emergency alerts.

# Mountain Climber Health & Location Tracker

Arduino-based wearable to monitor heart rate, temperature, and GPS location. Sends emergency SMS via GSM module on abnormal vitals.

## Features
- Heart-rate, body temperature, GPS tracking
- Emergency SMS alerts (SIM800L)
- On-device display for quick vitals

## Repo structure
- `firmware/` — Arduino sketches
- `hardware/` — circuit diagram & BOM
- `docs/` — setup & usage
- `images/` — photos/screenshots

## How to run (summary)
1. Open the appropriate `.ino` in Arduino IDE.
2. Install required libraries (Adafruit GPS, TinyGPS++ or similar, SoftwareSerial, LiquidCrystal).
3. Upload to Arduino/ESP32.
