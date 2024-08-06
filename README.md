# Fan and Light & Washer and Dryer Control with Arduino and ESP8266

This project involves using an Arduino and ESP8266 to control a fan and a light using buttons, and send their status to Firebase. Additionally, it includes another Arduino sketch for controlling a washer and a dryer with countdown timers displayed on 7-segment displays, and sending data to Google Sheets.

## Project Overview

This project is part of the Microprocessor and Internet of Things course. It consists of two main Arduino sketches:

1. **Fan and Light Control** (`FanAndLight.ino`): Controls a fan and a light using buttons, and updates their status on Firebase.
2. **Washer and Dryer Countdown** (`WasherAndDryer.ino`): Controls a washer and a dryer with countdown timers displayed on 7-segment displays, and sends data to Google Sheets.

## Requirements

- Arduino IDE
- ESP8266 Board
- Firebase Account
- Google Sheets and Google Apps Script
- Libraries: `ESP8266WiFi`, `TM1637Display`, `FirebaseArduino`

## Hardware Connections

### Fan and Light Control

- **Fan Button**: D1
- **Fan LED**: D0
- **Light Button**: D6
- **Light LED**: D5

### Washer and Dryer Countdown

- **Washer Button**: D2
- **Washer 7-segment Display**: CLK1 (D1), DIO1 (D0)
- **Dryer Button**: D4
- **Dryer 7-segment Display**: CLK2 (D6), DIO2 (D5)

## Setup Instructions

1. **WiFi Configuration**:
   - Modify the `SSID_1` and `PASS_1` defines in both `FanAndLight.ino` and `WasherAndDryer.ino` to match your WiFi credentials.

2. **Firebase Configuration**:
   - Set the `PROJECT_IO` and `DATA_SECRET` defines in `FanAndLight.ino` with your Firebase project name and secret.

3. **Google Sheets and Google Apps Script**:
   - Create a Google Apps Script to handle data sent from the ESP8266 and update the `GScriptId` define in `WasherAndDryer.ino` with your script ID.

4. **Upload Code**:
   - Upload `FanAndLight.ino` to control the fan and light.
   - Upload `WasherAndDryer.ino` to control the washer and dryer countdown timers.

## Usage

- **Fan and Light Control**:
  - Press the button connected to D1 to toggle the fan.
  - Press the button connected to D6 to toggle the light.
  - The status of the fan and light will be updated in Firebase.

- **Washer and Dryer Countdown**:
  - Press the button connected to D2 to start a 1-minute countdown for the washer.
  - Press the button connected to D4 to start a 1-minute countdown for the dryer.
  - The remaining time will be displayed on the 7-segment displays.
  - The status and time spent will be sent to Google Sheets.

## Web Interface

A web interface is available to view and update the status of the fan, light, washer, and dryer. It retrieves data from Google Sheets and Firebase and allows updating Firebase data.

## Acknowledgements

This project is part of the Microprocessor and Internet of Things course and was developed to demonstrate the integration of Arduino with Firebase and Google Sheets for IoT applications.
