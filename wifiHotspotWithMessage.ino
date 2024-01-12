#include <WiFi.h>
#include "arduino_secrets.h"
#include "ArduinoGraphics.h"
#include "Arduino_LED_Matrix.h"

// WiFi credentials from arduino_secrets.h
char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASS;

ArduinoLEDMatrix matrix;

void setup() {
  Serial.begin(115200);
  matrix.begin();

  // Attempt to connect to WiFi network
  Serial.println("Connecting to WiFi...");
  displayScrollingMessage("Connecting...");

  WiFi.begin(ssid, pass);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  // Once connected, print the IP Address
  Serial.println("");
  Serial.print("Connected! IP address: ");
  Serial.println(WiFi.localIP());

  // Display connection success and IP Address on the LED matrix
  String ipMessage = "Connected! IP: " + WiFi.localIP().toString();
  displayScrollingMessage(ipMessage.c_str());
  delay(5000); // Keep the message for a while before starting the loop
}

void loop() {
  // Scroll the IP address continuously
  String ipMessage = "IP: " + WiFi.localIP().toString();
  displayScrollingMessage(ipMessage.c_str());
  delay(2000); // Adjust the delay and scroll speed as needed
}

void displayScrollingMessage(const char *message) {
  matrix.beginDraw();
  matrix.stroke(0xFFFFFFFF);
  matrix.textFont(Font_5x7);
  matrix.textScrollSpeed(70); // Adjust scroll speed as needed

  // Start scrolling the text
  matrix.beginText(0, 1, 0xFFFFFF);
  matrix.println(message);
  matrix.endText(SCROLL_LEFT);

  matrix.endDraw();
}
