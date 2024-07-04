#include "Particle.h"

#include "BeaconScanner.h"
#include "GPIO.h"
#include "GPS.h"

SerialLogHandler logHandler(115200, LOG_LEVEL_INFO);
SYSTEM_THREAD(ENABLED);
SYSTEM_MODE(SEMI_AUTOMATIC);

BeaconScanner scanner;
GPS gps;
GPIOmonitor gpio;

const char* prepareJSON();
void systemToJSON(JSONWriter* json);

void setup() {
    delay(2000);
    Log.info("Setting up.");

    scanner.start();
    gps.start();
    gpio.setup();

    Cellular.on();
    Particle.connect();
}

const unsigned long PUBLISH_PERIOD = 300000;
unsigned long lastPublish = 0;
const unsigned long SERIAL_PERIOD = 5000;
unsigned long lastSerial = 0;

void loop() {
    gpio.loop();

    if (millis() - lastSerial >= SERIAL_PERIOD) {
        lastSerial = millis();
        const char* json = prepareJSON();
        Log.print(json);
        Log.print("\n---\n");

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
    gpio.toJSON(&json);
    systemToJSON(&json);
    json.endObject();
    size_t size = std::min(json.bufferSize(), json.dataSize());
    json.buffer()[size] = '\0';
    return json.buffer();
}

int percent10(float f) {
    if (f < 0.0) return -1;
    return (int)(10.0f * f);
}

void systemToJSON(JSONWriter* json) {
    json->name("sys");
    json->beginObject();
    json->name("ps").value(System.powerSource());
    json->name("soc").value(percent10(System.batteryCharge()));
    json->name("mem").value(System.freeMemory());
    CellularSignal cs = Cellular.RSSI();
    json->name("ss").value(percent10(cs.getStrength()));
    json->name("sq").value(percent10(cs.getQuality()));
    json->endObject();
}
