# HomeAutomation
# 📡 ESP32 Smart Light Control Using WiFi (4-Channel Relay)

## 🧠 Introduction

This project demonstrates how to build a simple **IoT-based home automation system** using an ESP32 microcontroller and a 4-channel relay module. The system allows users to control electrical appliances (like lights) through a web interface hosted on the ESP32, accessible via a mobile phone or computer browser over WiFi.

---

## 🎯 Objectives

* Control up to 4 electrical devices remotely
* Use a mobile browser as the control interface
* Learn basics of IoT, ESP32, and web servers
* Implement a low-cost smart home solution

---

## 🧰 Components Required

| Component               | Quantity  |
| ----------------------- | --------- |
| ESP32 Development Board | 1         |
| 4-Channel Relay Module  | 1         |
| Jumper Wires            | As needed |
| WiFi Router             | 1         |
| Mobile Phone / PC       | 1         |

---

## ⚠️ Safety Precautions

* This project involves **AC mains voltage**, which is dangerous.
* Always disconnect power while wiring.
* If unsure, consult an electrician.
* Ensure proper insulation and secure connections.

---

## 🔌 Hardware Connections

### Relay Module to ESP32

| Relay Pin | ESP32 Pin |
| --------- | --------- |
| VCC       | 5V        |
| GND       | GND       |
| IN1       | GPIO 23   |
| IN2       | GPIO 22   |
| IN3       | GPIO 21   |
| IN4       | GPIO 19   |

---

### AC Load Connection

Each relay has:

* COM (Common)
* NO (Normally Open)
* NC (Normally Closed)

#### Recommended Wiring:

* Phase wire → COM
* NO → Appliance (Light)
* Neutral → Direct to appliance

👉 The appliance turns ON when the relay is activated.

---

## 💻 Software Setup

### Step 1: Install Arduino IDE

Download and install Arduino IDE from the official website.

---

### Step 2: Install ESP32 Board Package

1. Open Arduino IDE
2. Go to **File → Preferences**
3. Add this URL in "Additional Board Manager URLs":

```
https://dl.espressif.com/dl/package_esp32_index.json
```

4. Go to **Tools → Board → Board Manager**
5. Search for **ESP32**
6. Install **ESP32 by Espressif Systems**

---

### Step 3: Select Board

Go to:

```
Tools → Board → ESP32 Arduino → DOIT ESP32 DEVKIT V1
```

---

## 🧾 Program Code

```cpp
#include <WiFi.h>

// WiFi credentials
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

    if (request.indexOf("/relay1/on") != -1) digitalWrite(relay1, LOW);
    if (request.indexOf("/relay1/off") != -1) digitalWrite(relay1, HIGH);

    if (request.indexOf("/relay2/on") != -1) digitalWrite(relay2, LOW);
    if (request.indexOf("/relay2/off") != -1) digitalWrite(relay2, HIGH);

    if (request.indexOf("/relay3/on") != -1) digitalWrite(relay3, LOW);
    if (request.indexOf("/relay3/off") != -1) digitalWrite(relay3, HIGH);

    if (request.indexOf("/relay4/on") != -1) digitalWrite(relay4, LOW);
    if (request.indexOf("/relay4/off") != -1) digitalWrite(relay4, HIGH);

    // Web interface
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
```

---

## 📱 How It Works

1. ESP32 connects to WiFi network
2. It starts a web server
3. Displays a control page in browser
4. User clicks ON/OFF links
5. ESP32 receives request
6. Relay switches ON/OFF
7. Device (light) responds

---

## 🌐 Accessing the System

1. Upload code to ESP32
2. Open Serial Monitor (115200 baud)
3. Note the IP address (e.g., 192.168.1.5)
4. Open browser on mobile
5. Enter IP address

---

## 🚀 Features

* Wireless control via WiFi
* No external app required
* Supports multiple devices
* Low cost and scalable

---

## 🔧 Troubleshooting

| Issue                | Solution                          |
| -------------------- | --------------------------------- |
| ESP32 not connecting | Check WiFi credentials            |
| Upload fails         | Press BOOT button while uploading |
| Page not loading     | Verify IP and network             |
| Relay not working    | Check HIGH/LOW logic              |
| No Serial output     | Press reset button                |

---

## 🔮 Future Enhancements

* Add modern UI (HTML + CSS)
* Password authentication
* Mobile app integration
* Voice control (Google Assistant)
* Timer-based automation
* Cloud-based remote access

---

## 🧩 Conclusion

This project provides a solid introduction to IoT and home automation using ESP32. With minimal components and basic programming, you can build a functional smart home system and expand it further with advanced features.

---

## 🏷️ Keywords (for SEO)

ESP32 IoT Project, Smart Home Automation, ESP32 Relay Control, WiFi Light Control, Arduino ESP32 Web Server

---

## 🙌 Author Notes

This project is beginner-friendly and can be enhanced into a full-fledged home automation system. Experiment with UI, cloud integration, and voice assistants to take it to the next level.
