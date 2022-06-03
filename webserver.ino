// Load Wifi libary
#include <WiFi.h>
#include <WebServer.h>

// network credentials
const char* ssid = "TQ-Visitors";
const char* password = "Toq2005+";

// IP Address details
IPAddress local_ip(192,168,1,144);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0); 

// Set web server port number to 80
WebServer server(80);

void setup() {
  // put your setup code here, to run once:

  // Connect to Wi-Fi network with SSID and password
  Serial.print("Connecting to ");
  Serial.println(ssid);
  Wifi.begin(ssid, password);
  
  while (Wifi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  Serial.println("");
  Serial.println("Wifi connected.");
  Serial.println("IP address: ");
  Serial.println(Wifi.localIP());
  server.begin();
  Serial.println("HTTP server started");
}

void loop() {
  server.handleClient();
}

void handle_OnConnect() {
  server.send(200, "text/html", SendHTML());
}

void handle_NotFound() {
  server.send(404, "text/plain", "Not found");
}

String SendHTML() {
    String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Web Server Test</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web Server</h1>\n";
  ptr +="<h3>Using Access Point(AP) Mode</h3>\n";

  return ptr;
}
