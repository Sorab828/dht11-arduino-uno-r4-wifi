# DHT11 + Arduino UNO R4 WiFi

Project that reads temperature and humidity from a DHT11 sensor and displays the results on a small I2C OLED display. Built with PlatformIO and the Arduino framework; intended to be opened in CLion (PlatformIO plugin).

---

## Quick checklist

- Open the project in CLion (see "Using CLion" below).
- Build using PlatformIO (environment: `uno_r4_wifi`).
- Upload to your UNO R4 WiFi and open serial monitor on the configured COM port.

---

## Project overview

This repository contains the firmware and configuration to run a DHT11 (temperature/humidity) sensor together with an I2C OLED display on an Arduino UNO R4 WiFi board. The project uses PlatformIO for build and upload and depends on the Adafruit sensor libraries.

Files to know:
- `platformio.ini` — project configuration and library dependencies.
- `src/main.cpp` — main application code (read sensor, update display, serial output).

---

## Using CLion

Recommended workflow:
1. Install CLion (see "IDE version" below) on your machine.
2. Install the PlatformIO plugin for CLion (or use PlatformIO IDE in VS Code if preferred).
3. In CLion: File → Open... → select the project root (this folder). PlatformIO should detect the `platformio.ini` file.
4. Use the PlatformIO tool window to Build, Upload, and Monitor the serial output.

IDE troubleshooting tips:
- If CLion doesn't detect PlatformIO, ensure the PlatformIO CLI (platformio) is installed and available in your PATH.
- If the project tree looks incomplete, rebuild the project index (File → Invalidate Caches / Restart).

---

## IDE version

Assumption/Recommendation: This README was written assuming a modern CLion release. Recommended:
- CLion 2023.3 or newer (any recent stable release should work).
- PlatformIO Core (CLI) 6.x or later and the PlatformIO plugin compatible with your CLion version.

If you use a different IDE (for example VS Code) the PlatformIO steps below still apply.

---

## Code (where and how)

Primary code location: `src/main.cpp`.

A minimal example of how the sketch typically works (example only — check `src/main.cpp` in this repo for the actual implementation):

```cpp
#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>

#define DHTPIN 2
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
Adafruit_SSD1306 display(128, 64, &Wire);

void setup() {
  Serial.begin(9600);
  dht.begin();
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
}

void loop() {
  float hum = dht.readHumidity();
  float temp = dht.readTemperature();
  if (isnan(hum) || isnan(temp)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }
  Serial.printf("Temp: %.1f C  Hum: %.1f %%\n", temp, hum);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.printf("Temp: %.1f C\nHum: %.1f %%", temp, hum);
  display.display();
  delay(2000);
}
```

---

## Libraries and dependencies

The libraries configured in `platformio.ini` for this project (as of the committed configuration):

- arduino-libraries/Servo@^1.3.0
- adafruit/DHT sensor library@^1.4.6
- adafruit/Adafruit Unified Sensor@^1.1.15

Notes and additional common libraries you may want for an OLED display (not all are required unless your `src/main.cpp` uses them):
- Adafruit SSD1306 (common for I2C OLED displays)
- Adafruit GFX (graphics support used by SSD1306)

If your code needs SSD1306/GFX, add them to `lib_deps` in `platformio.ini`, for example:

```
Adafruit SSD1306@^2.0.0
Adafruit GFX Library@^1.11.0
```

(Adjust versions to match PlatformIO available releases.)

---

## Hardware components and wiring (OLED details)

Typical components used:
- Arduino UNO R4 WiFi (board defined in `platformio.ini` as `uno_r4_wifi`).
- DHT11 temperature/humidity sensor.
- Small I2C OLED display (e.g., 128x32 or 128x64 SSD1306-based). Verify your display controller.
- Jumper wires and breadboard.

Suggested wiring:
- DHT11
  - VCC → 5V (or 3.3V if your DHT module requires it)
  - GND → GND
  - DATA → digital pin D2 (use a 4.7K–10K pull-up resistor between DATA and VCC if required by your module)

- OLED (I2C)
  - VCC → 3.3V or 5V (check your OLED module voltage requirements)
  - GND → GND
  - SDA → board SDA pin (on classic UNO this is A4; on UNO R4 check the board silks or documentation)
  - SCL → board SCL pin (on classic UNO this is A5)

Important: UNO R4 WiFi pin mappings differ slightly from classic UNO; always confirm the correct SDA/SCL pins on your board's schematic or silkscreen.

---

## Build and upload (PlatformIO)

Using CLion PlatformIO GUI:
- Select environment `uno_r4_wifi`.
- Click Build (hammer icon) to compile.
- Click Upload (right-arrow) to upload to your board.
- Click Monitor (plug icon) to open the serial monitor.

PlatformIO CLI (from project root):

```powershell
# build
pio run -e uno_r4_wifi

# upload
pio run -e uno_r4_wifi -t upload

# open serial monitor (default baud set in platformio.ini: 9600)
pio device monitor -e uno_r4_wifi -b 9600 -p COM12
```

Note: `COM12` is set in `platformio.ini` in this repo — change it to your board's port if different.

---

## Troubleshooting

- Build errors about missing libraries: run `pio lib install` or add the missing libraries to `lib_deps` in `platformio.ini`.
- Upload errors: verify upload_port, close other programs (serial monitor), and ensure correct board selection in `platformio.ini`.
- OLED shows no text: check I2C address (common addresses: 0x3C or 0x3D), wiring, and that your code initializes the correct display size and address.

---

## Author

Author: Replace this line with your name.

Repository owner: (update as needed)

---

If you'd like, I can:
- Add SSD1306 + Adafruit GFX to `platformio.ini` `lib_deps` directly (safe change).
- Extract or summarize the real `src/main.cpp` contents into this README (so the README matches the actual code).

Tell me which of the above you'd like and I will update the repo accordingly.
