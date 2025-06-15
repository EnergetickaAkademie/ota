# EA-OTA Library

A comprehensive OTA (Over-The-Air) updates and WebSerial debugging library for ESP8266 Arduino projects by Energetická Akademie.

## Features

- **OTA Updates**: Wireless firmware updates via WiFi
- **WebSerial Debug**: Web-based debugging console
- **mDNS Support**: Easy device discovery using `.local` hostnames
- **Auto WiFi Connection**: Automatic WiFi connection with retry logic
- **Progress Monitoring**: Real-time OTA update progress
- **Error Handling**: Comprehensive error reporting

## Dependencies

This library automatically handles the following dependencies:
- `ayushsharma82/WebSerial` - Web-based serial monitor
- `ottowinter/ESPAsyncWebServer-esphome` - Async web server
- Built-in ESP8266 libraries: WiFi, mDNS, ArduinoOTA

## Installation

### PlatformIO
Add to your `platformio.ini`:
```ini
lib_deps = 
    https://github.com/EnergetickaAkademie/ota.git
```

## Usage

### Basic Setup

```cpp
#include <ota.h>

void setup() {
    Serial.begin(115200);
    
    // Connect to WiFi
    connectWifi("your_ssid", "your_password");
    
    // Setup OTA with hostname and password
    setupOTA(-1, "MyDevice", "admin");
    
    // Setup WebSerial debugging
    setupWebSerial("MyDevice");
    
    Serial.println("Ready!");
}

void loop() {
    // Handle OTA updates and mDNS
    handleOTA();
    
    // Your application code here
    
    // Send debug info to WebSerial
    WebSerial.println("Debug message");
}
```

### Function Reference

#### `connectWifi(ssid, password)`
Connects to WiFi network with automatic retry and restart on failure.

**Parameters:**
- `ssid` - WiFi network name
- `password` - WiFi password

#### `setupOTA(port, hostname, password)`
Configures OTA updates with mDNS support.

**Parameters:**
- `port` - OTA port (default: 8266, use -1 for default)
- `hostname` - Device hostname for mDNS (default: "OneWireSlave")
- `password` - OTA password (optional)

#### `setupWebSerial(hostname)`
Initializes WebSerial web interface for remote debugging.

**Parameters:**
- `hostname` - Device hostname (should match OTA hostname)

#### `handleOTA()`
Call this in your main loop to handle OTA updates and mDNS.

### WebSerial Access

After setup, access the web debug console at:
- `http://[device-hostname].local/webserial`
- `http://[ip-address]/webserial`

### OTA Updates

Configure your PlatformIO environment for OTA:
```ini
[env:ota]
platform = espressif8266
board = your_board
framework = arduino
upload_protocol = espota
upload_port = MyDevice.local
upload_flags = --auth=admin
```

## Example Projects

See the [examples](examples/) directory for complete project examples.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## Support

For support and questions, please open an issue on GitHub.