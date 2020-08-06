#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 23
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
DeviceAddress insideThermometer;

#include <WiFi.h>
const char* ssid     = "Hallym WiFi";
const char* password = "1111133333";
const char* host = "api.thingspeak.com";
String url = "/update?api_key=XMFKVF94NW54PH45&field1=";
static unsigned long mark;

void send(float temp) {
    WiFiClient client;
    const int httpPort = 80;
    if (!client.connect(host, httpPort)) {
        Serial.println("connection failed");
        return;
    }

    // We now create a URI for the request
    url += String(temp);

    Serial.print("\nRequesting URL: ");
    Serial.println(url);

    // This will send the request to the server
    client.print(String("GET ") + url + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n\r\n");
    unsigned long timeout = millis();
    while (client.available() == 0) {
        if (millis() - timeout > 5000) {
            Serial.println(">>> Client Timeout !");
            client.stop();
            return;
        }
    }

    // Read all the lines of the reply from server and print them to Serial
    while(client.available()) {
        String line = client.readStringUntil('\r');
        Serial.print(line);
    }	
}

void ticker() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempC(insideThermometer);
  Serial.print(tempC);
  send(tempC);
}

void setup() {
	Serial.begin(115200);
	sensors.begin();
	Serial.print("Found ");
	Serial.print(sensors.getDeviceCount(), DEC);
	Serial.print("Device 0 Resolution: ");
	Serial.print(sensors.getResolution(insideThermometer), DEC); 
	Serial.println();
	if (!sensors.getAddress(insideThermometer, 0)) 
		Serial.println("Unable to find address for Device 0"); 

	WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
    mark = millis() + 2000;
}

void loop() {
    if (millis() > mark) {
        mark = millis() + 20000;
		ticker();
	}
}
