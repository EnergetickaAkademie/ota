#include "ota.h"

AsyncWebServer server(80);

void connectWifi(const char* ssid, const char* password){
	WiFi.mode(WIFI_STA);
	WiFi.begin(ssid, password);
	while (WiFi.waitForConnectResult() != WL_CONNECTED) {
		Serial.println("Connection Failed! Rebooting...");
		delay(5000);
		ESP.restart();
	}
}

void setupOTA(int port, const char* hostname, const char* password) {
	// Port defaults to 8266
	const char* defaultHostname = "OneWireSlave";
	const char* actualHostname = (hostname != nullptr) ? hostname : defaultHostname;

	if (port > 0){
		ArduinoOTA.setPort(port);
	}

	ArduinoOTA.setHostname(actualHostname);

	if (password != nullptr) {
		ArduinoOTA.setPassword(password);
	}

	// Initialize mDNS
	if (!MDNS.begin(actualHostname)) {
		Serial.println("Error setting up MDNS responder!");
	} else {
		Serial.print("mDNS responder started. Hostname: ");
		Serial.print(actualHostname);
		Serial.println(".local");
	}

	ArduinoOTA.onStart([]() {
		String type;
		if (ArduinoOTA.getCommand() == U_FLASH) {
			type = "sketch";
		} else { // U_SPIFFS
			type = "filesystem";
		}
		Serial.println("Start updating " + type);
	});
	
	ArduinoOTA.onEnd([]() {
		Serial.println("\nEnd");
	});
	
	ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
	});

	ArduinoOTA.onError([](ota_error_t error) {
Serial.printf("Error[%u]: ", error);
		if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
		else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
		else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
		else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
		else if (error == OTA_END_ERROR) Serial.println("End Failed");
	});
	ArduinoOTA.begin();
	
	// Add mDNS service for OTA
	MDNS.addService("arduino", "tcp", 8266);
}

void setupWebSerial(const char* hostname) {
	const char* defaultHostname = "OneWireSlave";
	const char* actualHostname = (hostname != nullptr) ? hostname : defaultHostname;
	
	// WebSerial is accessible at "<IP Address>/webserial" in browser
	WebSerial.begin(&server);
	
	// Optional: Set a callback for received messages
	WebSerial.msgCallback([](uint8_t *data, size_t len){
String d = "";
		for(size_t i=0; i < len; i++){
			d += char(data[i]);
		}
		WebSerial.println("Received Data: " + d);
		Serial.println("Received from WebSerial: " + d);
	});
	
	server.begin();
	
	Serial.println("WebSerial initialized!");
	Serial.print("Open browser and go to: http://");
	Serial.print(WiFi.localIP());
	Serial.println("/webserial");
	Serial.print("Or use: http://");
	Serial.print(actualHostname);
	Serial.println(".local/webserial");
}

void handleOTA(){
	ArduinoOTA.handle();
#ifdef ESP8266
	MDNS.update();
#endif
}
