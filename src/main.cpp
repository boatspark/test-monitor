#include "Particle.h"

#include "BeaconScanner.h"
#include "GPS.h"

SerialLogHandler logHandler(115200, LOG_LEVEL_INFO);
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

BeaconScanner scanner;
GPS gps;
const char* prepareJSON();

void setup() {
    delay(2000);
    Log.info("Setting up.");

    scanner.start();
    gps.start();

    Cellular.on();
    Particle.connect();
}

const unsigned long PUBLISH_PERIOD = 300000;
unsigned long lastPublish = 0;
const unsigned long SERIAL_PERIOD = 5000;
unsigned long lastSerial = 0;

void loop() {
    if (millis() - lastSerial >= SERIAL_PERIOD) {
        lastSerial = millis();
        const char* json = prepareJSON();
        Serial.println(json);

        if (Particle.connected()) {
            if (millis() - lastPublish >= PUBLISH_PERIOD) {
                lastPublish = millis();
                Particle.publish("monitor", json);
            }
        }
    }
}

char jsonbuf[512];
const char* prepareJSON() {
    JSONBufferWriter json(jsonbuf, sizeof(jsonbuf) - 1);
    json.beginObject();
    scanner.toJSON(&json);
    gps.toJSON(&json);
    json.endObject();
    size_t size = std::min(json.bufferSize(), json.dataSize());
    json.buffer()[size] = '\0';
    return json.buffer();
}
