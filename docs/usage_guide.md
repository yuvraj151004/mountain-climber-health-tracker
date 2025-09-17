# Usage Guide

## Wiring (example)
- Heartbeat sensor → A0
- Temperature sensor (LM35) → A1
- GSM Module → TX/RX (pins 7, 8 in firmware)
- GPS Module → Connected via SoftwareSerial
- LCD → I2C (address 0x27)

## How to Test
1. Power on the system with Arduino + modules connected.
2. Wait for "Searching Network..." on LCD.
3. Send SMS with the word `LOCAL` to the SIM card in the GSM module.
4. The device replies with:
   - Temperature
   - Heartbeat
   - Google Maps location link
5. Press the SOS button → device automatically sends emergency alert + location.

## Expected Output
- LCD cycles through temperature & heartbeat.
- SMS includes live coordinates in format:  
  `http://maps.google.com/maps?q=loc:LAT,LON`
