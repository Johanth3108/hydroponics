# Hydroponics Project with ESP8266

## Introduction
This repository contains the code for a hydroponics project implemented using ESP8266 microcontroller. The project aims to monitor and control various parameters of a hydroponic system such as temperature, pH level, and total dissolved solids (TDS) remotely using a web server.

## Components Used
- ESP8266 microcontroller
- DS18B20 temperature sensor
- pH sensor
- TDS sensor
- WiFi module
- Breadboard and jumper wires

## Libraries Used
- SoftwareSerial
- ESP8266WiFi
- WiFiClient
- ESP8266WebServer
- OneWire
- DallasTemperature

## Setup Instructions
1. Connect the hardware components according to the circuit diagram provided.
2. Upload the provided code to the ESP8266 microcontroller.
3. Update the following variables in the code to match your WiFi network credentials:
   - `ssid`: Your WiFi network SSID
   - `password`: Your WiFi network password
4. Update the `GAS_ID` variable with the Google Apps Script ID for your Google Sheet where the data will be logged.
5. Compile and upload the code to the ESP8266 microcontroller.
6. Open the serial monitor to view the debug messages and ensure the ESP8266 connects to the WiFi network successfully.
7. Access the web server hosted by the ESP8266 by navigating to its IP address in a web browser.

## Usage
- Upon successful setup and connection, the ESP8266 will continuously monitor the sensors and update the Google Sheet with the data.
- The web server provides endpoints to retrieve sensor data and control the system remotely.

## Files Description
- `index.h`: HTML code for the web server homepage.
- `README.md`: Instructions and information about the project (this file).
- `hydroponics_project_ESP8266`: Arduino sketch file containing the code for the hydroponics project.

## Contributing
Feel free to contribute to this project by submitting bug reports, feature requests, or pull requests. Your contributions are highly appreciated.

## Acknowledgments
- Special thanks to the authors of the libraries used in this project for their contributions.
- Inspiration for this project came from the need for remote monitoring and control of hydroponic systems for efficient plant growth.

---
By Johanth PS
