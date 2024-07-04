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

const char* prepareReport();
const char* prepareAlert(uint8_t alert);
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
unsigned long lastAlert[3] = {0, 0, 0};
const unsigned long ALERT_PERIOD = 60000;

bool checkAlert(uint8_t alert, GPIOmonitor::AlertState check, int index) {
    bool publish = false;
    if ((alert & check) && (millis() - lastAlert[index] >= ALERT_PERIOD)) {
        lastAlert[index] = millis();
        publish = true;
    }
    return publish;
}

void loop() {
    gpio.loop();

    if (Particle.connected()) {
        uint8_t alert = gpio.alert();  // this also resets alert status
        if (alert != GPIOmonitor::ALERT_NONE) {
            // Alert has been triggered
            // Determine whether to publish alert
            bool publish = false;
            if (checkAlert(alert, GPIOmonitor::ALERT_BILGEPUMP, 0)) publish = true;
            if (checkAlert(alert, GPIOmonitor::ALERT_SHOREPOWER_LOST, 1)) publish = true;
            if (checkAlert(alert, GPIOmonitor::ALERT_SHOREPOWER_RESTORED, 2)) publish = true;
            if (publish) {
                const char* json = prepareAlert(alert);
                Particle.publish("alert", json);
            }
        }
    }

    if (millis() - lastSerial >= SERIAL_PERIOD) {
        lastSerial = millis();
        const char* json = prepareReport();
        Log.print(json);
        Log.print("\n---\n");

        Log.info("Time since publish: %ld", millis() - lastPublish);

        if (Particle.connected()) {
            if (millis() - lastPublish >= PUBLISH_PERIOD) {
                lastPublish = millis();
                Particle.publish("monitor", json);
            }
        }
    }
}

char jsonbuf[512];
const char* terminateJson(JSONBufferWriter& json) {
    size_t size = std::min(json.bufferSize(), json.dataSize());
    json.buffer()[size] = '\0';
    return json.buffer();
}

const char* prepareReport() {
    JSONBufferWriter json(jsonbuf, sizeof(jsonbuf) - 1);
    json.beginObject();
    scanner.toJSON(&json);
    gps.toJSON(&json);
    gpio.toJSON(&json);
    systemToJSON(&json);
    json.endObject();
    return terminateJson(json);
}

const char* prepareAlert(uint8_t alert) {
    JSONBufferWriter json(jsonbuf, sizeof(jsonbuf) - 1);
    json.beginObject();
    json.name("alert").value(alert);
    gpio.toJSON(&json);
    systemToJSON(&json);
    json.endObject();
    return terminateJson(json);
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
