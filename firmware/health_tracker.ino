#define BLYNK_TEMPLATE_NAME "yuvraj"
#define BLYNK_AUTH_TOKEN "9qCkfMfAVioRXVNDOdfEbIJfNE49-mR-"
#include <TinyGPS.h>
#include <SoftwareSerial.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);
SoftwareSerial Gsm(7, 8);
char phone_no[] = "+918887506921"; // Replace with the phone number to get SMS

TinyGPS gps;  // Creates a new instance of the TinyGPS object
int state; 
String textMessage; 
const int sensor = A1;    // Temperature sensor pin
const int ldrPin = A0;    // Heartbeat sensor pin (LDR)

float tempc;  // Variable to store temperature in degree Celsius
float vout;   // Temporary variable to hold sensor reading

void setup() {
  Serial.begin(9600);  // Initialize Serial Monitor
  Gsm.begin(9600); 
  delay(2000);

  // AT command to set SIM900 to SMS mode
  Gsm.print("AT+CMGF=1\r"); 
  delay(100);

  // Set module to send SMS data to serial out upon receipt 
  Gsm.print("AT+CNMI=2,2,0,0,0\r");
  delay(100);

  pinMode(6, INPUT);
  pinMode(sensor, INPUT);
  pinMode(ldrPin, INPUT);

  lcd.begin(16, 2);
  lcd.backlight();
  lcd.clear();
  lcd.print("Searching ");
  lcd.setCursor(0, 1);
  lcd.print("Network....... "); 
  delay(3000);
}

void loop() {
  lcd.clear();
  lcd.print("Mountain Climber");
  lcd.setCursor(0, 1);
  lcd.print("Tracking System");
  delay(1000);

  // Read temperature
  vout = analogRead(sensor);  // Read the value from the temperature sensor
  vout = (vout * 500) / 1023; // Convert to millivolts and then Celsius
  tempc = vout;

  // Read LDR status (heartbeat simulation)
  int ldrStatus = analogRead(ldrPin);  // Read light sensor value for heartbeat

  // Display Temperature and Heartbeat on LCD
  lcd.clear();
  lcd.print("Temp: ");
  lcd.print(tempc);
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Heartbeat: ");
  lcd.print(ldrStatus / 10);
  delay(2000);

  // Print Temperature and Heartbeat values to Serial Monitor
  Serial.print("Temperature: ");
  Serial.print(tempc);
  Serial.print(" °C\t");
  Serial.print("Heartbeat: ");
  Serial.println(ldrStatus / 10);

  // Send data to Serial Plotter for graphing
  Serial.print("Temperature: ");
  Serial.print(tempc);
  Serial.print("\t");
  Serial.print("Heartbeat: ");
  Serial.println(ldrStatus / 10);

  // Process incoming SMS
  if (Gsm.available() > 0) {
    textMessage = Gsm.readString();
    textMessage.toUpperCase();
    delay(10);
  }

  // Check for 'LOCAL' command in the received SMS
  if (textMessage.indexOf("LOCAL") >= 0) {
    lcd.clear();
    lcd.print("Message Received");
    delay(3000);
    lcd.clear();
    lcd.print("Getting ");
    lcd.setCursor(0, 1);
    lcd.print("Location...");
    delay(3000);

    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);

    Gsm.print("AT+CMGF=1\r"); 
    delay(400);
    Gsm.print("AT+CMGS=\"");
    Gsm.print(phone_no);
    Gsm.println("\"");

    lcd.clear();
    lcd.print("Sending location");
    lcd.setCursor(0, 1);
    lcd.print("To Base...");
    delay(3000);

    Gsm.println("Yuvraj, Battalion No. 1233456");
    Gsm.print("Temperature: ");
    Gsm.println(tempc);

    Gsm.print("Heartbeat: ");
    Gsm.println(ldrStatus / 10);

    Gsm.print("http://maps.google.com/maps?q=loc:");
    Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Gsm.print(",");
    Gsm.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(200);
    Gsm.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    Gsm.println();
    delay(10000);

    lcd.clear();
    lcd.print("Location Sent");
    delay(3000);
  }

  // Handle SOS alert
  state = digitalRead(6);
  if (state == 1) {
    float flat, flon;
    unsigned long age;
    gps.f_get_position(&flat, &flon, &age);

    Gsm.print("AT+CMGF=1\r"); 
    delay(400);
    Gsm.print("AT+CMGS=\"");
    Gsm.print(phone_no);
    Gsm.println("\"");

    lcd.clear();
    lcd.print("Sending SOS...");
    lcd.setCursor(0, 1);
    lcd.print("Location to Base");
    delay(3000);

    Gsm.println("Alert! I need help. Yuvraj, Battalion No. 1233456");
    Gsm.print("Temperature: ");
    Gsm.println(tempc);

    Gsm.print("Heartbeat: ");
    Gsm.println(ldrStatus / 10);

    Gsm.print("http://maps.google.com/maps?q=loc:");
    Gsm.print(flat == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flat, 6);
    Gsm.print(",");
    Gsm.print(flon == TinyGPS::GPS_INVALID_F_ANGLE ? 0.0 : flon, 6);
    delay(200);
    Gsm.println((char)26); // End AT command with a ^Z, ASCII code 26
    delay(200);
    Gsm.println();
    delay(10000);

    lcd.clear();
    lcd.print("SOS Sent");
    delay(3000);
  } else {
    lcd.clear();
    lcd.print("Soldier Tracking");
    lcd.setCursor(0, 1);
    lcd.print("System Active");
    delay(2000);
  }
}
