#include "Particle.h"

#include "BeaconScanner.h"
#include "GPS.h"

SerialLogHandler logHandler(115200, LOG_LEVEL_INFO);
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

BeaconScanner scanner;
GPS gps;

void setup() {
    delay(2000);
    Log.info("Setting up.");

    scanner.start();
    gps.start();
}

char buf[512];

void loop() {
    delay(2000);

    JSONBufferWriter json(buf, sizeof(buf) - 1);
    json.beginObject();
    scanner.toJSON(&json);
    gps.toJSON(&json);
    json.endObject();
    size_t size = std::min(json.bufferSize(), json.dataSize());
    json.buffer()[size] = '\0';
    Serial.println(buf);
}
