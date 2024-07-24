#include <WiFi.h>
#include <Wire.h>
#include <PubSubClient.h>

const char* ssid = "Vandyswifi";
const char* password = "-";
const char* mqtt_server = "192.168.235.244"; // IP address of your MQTT broker

const int esp32_address = 8; // I2C address of ESP32

WiFiClient espClient;
PubSubClient client(espClient);

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void callback(char* topic, byte* message, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)message[i]);
  }
  Serial.println();

  char command = (char)message[0]; // Get the command from the message

  // Send command to Arduino Uno via I2C
  Wire.beginTransmission(esp32_address);
  if (command == 'f') {
    Wire.write('F'); // Example: send 'F' for forward
    Serial.println("F");
  } else if (command == 'b') {
    Wire.write('B'); // Example: send 'B' for backward
    Serial.println("B");
  } else if (command == 'r') {
    Wire.write('R'); // Example: send 'R' for right
    Serial.println("R");
  } else if (command == 'l') {
    Wire.write('L'); // Example: send 'L' for left
    Serial.println("L");
  } else if (command == 's') {
    Wire.write('S'); // Example: send 'S' for stop
    Serial.println("S");
  }
  Wire.endTransmission();
}

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP32Client")) {
      Serial.println("connected");
      // Once connected, subscribe to the MQTT topic
      client.subscribe("esp32/control");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}

void setup() {
  Serial.begin(115200);
  Wire.begin();
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);
}

void loop() {
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
}
