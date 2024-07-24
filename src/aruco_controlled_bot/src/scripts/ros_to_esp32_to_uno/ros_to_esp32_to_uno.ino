  #include <WiFi.h>
  #include <Wire.h>

  const char* ssid = "Vandyswifi";
  const char* password = "Vanderboi007";
  const int esp32_address = 8; // I2C address of ESP32

  WiFiServer server(80);

  void setup() {
    Serial.begin(115200);
    delay(10);

    // Connect to Wi-Fi network
    Serial.println();
    Serial.print("Connecting to ");
    Serial.println(ssid);
    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected.");

    // Start the server
    server.begin();
    Serial.println("Server started");

    // Initialize I2C communication
    Wire.begin();
  }

  void loop() {
    WiFiClient client = server.available();
    if (!client) {
      return;
    }

    // Wait until the client sends some data
    
    while (!client.available()) {
      //delay(1);
    }

    // Read the first line of the request
    Serial.println("Received something");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();


    // Send command to Arduino Uno via I2C
    Wire.beginTransmission(esp32_address);
    if (request.indexOf("f") != -1) {
      Wire.write('F'); // Example: send 'F' for forward
      Serial.println("F");
    } else if (request.indexOf("b") != -1) {
      Wire.write('B'); // Example: send 'B' for backward
      Serial.println("B");
    } else if (request.indexOf("r") != -1) {
      Wire.write('R'); // Example: send 'R' for right
      Serial.println("R");
    } else if (request.indexOf("l") != -1) {
      Wire.write('L'); // Example: send 'L' for left
      Serial.println("L");
    } else if (request.indexOf("s") != -1) {
      Wire.write('S'); // Example: send 'S' for stop
      Serial.println("S");
    }
    Wire.endTransmission();
  }