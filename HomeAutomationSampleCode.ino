#include <WiFi.h>

// Replace with your WiFi credentials
const char* ssid = "YOUR_WIFI_NAME";
const char* password = "YOUR_WIFI_PASSWORD";

WiFiServer server(80);

// Relay pins
int relay1 = 23;
int relay2 = 22;
int relay3 = 21;
int relay4 = 19;

void setup() {
  Serial.begin(115200);

  pinMode(relay1, OUTPUT);
  pinMode(relay2, OUTPUT);
  pinMode(relay3, OUTPUT);
  pinMode(relay4, OUTPUT);

  // Turn OFF relays initially
  digitalWrite(relay1, HIGH);
  digitalWrite(relay2, HIGH);
  digitalWrite(relay3, HIGH);
  digitalWrite(relay4, HIGH);

  WiFi.begin(ssid, password);

  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("\nConnected!");
  Serial.println(WiFi.localIP());

  server.begin();
}

void loop() {
  WiFiClient client = server.available();

  if (client) {
    String request = client.readStringUntil('\r');
    client.flush();

    // Control relays
    if (request.indexOf("/relay1/on") != -1) digitalWrite(relay1, LOW);
    if (request.indexOf("/relay1/off") != -1) digitalWrite(relay1, HIGH);

    if (request.indexOf("/relay2/on") != -1) digitalWrite(relay2, LOW);
    if (request.indexOf("/relay2/off") != -1) digitalWrite(relay2, HIGH);

    if (request.indexOf("/relay3/on") != -1) digitalWrite(relay3, LOW);
    if (request.indexOf("/relay3/off") != -1) digitalWrite(relay3, HIGH);

    if (request.indexOf("/relay4/on") != -1) digitalWrite(relay4, LOW);
    if (request.indexOf("/relay4/off") != -1) digitalWrite(relay4, HIGH);

    // Webpage UI
    client.println("HTTP/1.1 200 OK");
    client.println("Content-Type: text/html");
    client.println("");

    client.println("<html><body>");
    client.println("<h2>ESP32 Light Control</h2>");

    client.println("<a href='/relay1/on'>Light 1 ON</a><br>");
    client.println("<a href='/relay1/off'>Light 1 OFF</a><br><br>");

    client.println("<a href='/relay2/on'>Light 2 ON</a><br>");
    client.println("<a href='/relay2/off'>Light 2 OFF</a><br><br>");

    client.println("<a href='/relay3/on'>Light 3 ON</a><br>");
    client.println("<a href='/relay3/off'>Light 3 OFF</a><br><br>");

    client.println("<a href='/relay4/on'>Light 4 ON</a><br>");
    client.println("<a href='/relay4/off'>Light 4 OFF</a><br>");

    client.println("</body></html>");

    client.stop();
  }
}
