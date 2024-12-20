#include "Particle.h"

#include "OledDisplay.h"
#include "oled-wing-adafruit.h"

OledDisplay::OledDisplay() : _display(nullptr) {}
OledDisplay::~OledDisplay() {
    if (_display != nullptr) delete _display;
}

void OledDisplay::setup() {
    if (_display == nullptr) {
        _display = new OledWingAdafruit();
    }
    _display->setup();
    _display->clearDisplay();
    _display->display();
}

void OledDisplay::loop() {
    _display->loop();
}

void OledDisplay::clear(u_int8_t size) {
    _display->clearDisplay();
    _display->setTextSize(size);
    _display->setTextColor(WHITE);
    _display->setCursor(0, 0);
}

size_t OledDisplay::println(const char* buf) {
    return _display->println(buf);
}

void OledDisplay::display() {
    _display->display();
}

// 'bs-splash', 128x32px
const unsigned char epd_bitmap_bs_splash[] = {
    0xef, 0xff, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xef, 0xff, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xef, 0xff, 0xf8, 0x02, 0xa8, 0x00, 0x00, 0x00, 0x00, 0x01, 0xf0, 0x00, 0x00, 0x00, 0x0c, 0x00,
    0xef, 0xff, 0xf8, 0x07, 0xfe, 0x00, 0x00, 0x03, 0x80, 0x07, 0xfc, 0x00, 0x00, 0x00, 0x1c, 0x00,
    0xef, 0xff, 0xf8, 0x07, 0xff, 0x00, 0x00, 0x03, 0x80, 0x07, 0xbc, 0x00, 0x00, 0x00, 0x1c, 0x00,
    0xef, 0xc3, 0xfc, 0x07, 0x07, 0x00, 0x00, 0x03, 0x80, 0x0e, 0x0e, 0x00, 0x00, 0x00, 0x1c, 0x00,
    0xef, 0xc3, 0xfc, 0x07, 0x07, 0x1f, 0x83, 0xf3, 0xfc, 0x0e, 0x0c, 0xef, 0x0f, 0xc6, 0xfc, 0x70,
    0xef, 0xc0, 0xf8, 0x07, 0x07, 0x3f, 0xcf, 0xfb, 0xfc, 0x0f, 0x00, 0xff, 0x9f, 0xe7, 0xfc, 0xf0,
    0xef, 0xc0, 0xf8, 0x07, 0xfe, 0x79, 0xee, 0x3b, 0x80, 0x07, 0xf0, 0xf3, 0x9c, 0x77, 0xdd, 0xe0,
    0xef, 0xe0, 0xf8, 0x07, 0xfe, 0x70, 0xe4, 0x3b, 0x84, 0x03, 0xfc, 0xe1, 0xc8, 0x77, 0x1f, 0xc0,
    0xef, 0xe0, 0xf0, 0x07, 0x57, 0xf0, 0xe3, 0xfb, 0x8c, 0x00, 0x7e, 0xe1, 0xc7, 0xf7, 0x1f, 0xc0,
    0xef, 0xf0, 0xe0, 0x07, 0x07, 0xf0, 0xef, 0xfb, 0x8c, 0x00, 0x0e, 0xe1, 0xdf, 0xf6, 0x1f, 0xc0,
    0xef, 0xff, 0x00, 0x07, 0x03, 0xf0, 0xee, 0x3b, 0x8c, 0x0e, 0x0f, 0xe1, 0xdc, 0x77, 0x1e, 0xe0,
    0xef, 0xff, 0xf0, 0x07, 0x07, 0x70, 0xee, 0x3b, 0x9c, 0x0e, 0x0e, 0xe3, 0xf8, 0x76, 0x1c, 0xe0,
    0xef, 0xff, 0xf8, 0x07, 0xff, 0x3f, 0xce, 0x7b, 0xfc, 0x07, 0xde, 0xff, 0x9d, 0xf7, 0x1c, 0x70,
    0xef, 0xff, 0xfe, 0x07, 0xfe, 0x3f, 0xcf, 0xf9, 0xf8, 0x07, 0xfc, 0xff, 0x9f, 0xf7, 0x1c, 0x70,
    0xe1, 0xff, 0xfe, 0x02, 0xd0, 0x0e, 0x03, 0x90, 0x70, 0x01, 0xf8, 0xe6, 0x0e, 0x44, 0x04, 0x20,
    0xec, 0x7f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
    0xef, 0x1f, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
    0xef, 0x87, 0xff, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
    0xef, 0xc3, 0xff, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xe0, 0x00, 0x00, 0x00, 0x00,
    0xef, 0xe1, 0xff, 0x80, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xef, 0xe0, 0xbf, 0x80, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xef, 0xe0, 0xff, 0x80, 0x02, 0x00, 0x00, 0x20, 0x00, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00,
    0xef, 0xe0, 0xbf, 0x80, 0x03, 0xc7, 0x8f, 0x33, 0xef, 0x1e, 0x7a, 0x21, 0xe3, 0xdf, 0x00, 0x00,
    0xef, 0xe0, 0xff, 0x00, 0x02, 0x24, 0x40, 0xa2, 0x08, 0x81, 0x42, 0x41, 0x12, 0x11, 0x00, 0x00,
    0xef, 0xe0, 0xff, 0x00, 0x02, 0x24, 0x47, 0xa3, 0x88, 0x8f, 0x42, 0x81, 0x12, 0x11, 0x00, 0x00,
    0xef, 0xf5, 0xff, 0x00, 0x02, 0x24, 0x48, 0x20, 0x68, 0x90, 0x43, 0x41, 0x12, 0x11, 0x00, 0x00,
    0xef, 0xff, 0xfe, 0x00, 0x02, 0x24, 0x48, 0xa0, 0x28, 0x91, 0x42, 0x41, 0x12, 0x11, 0x00, 0x00,
    0xef, 0xff, 0xfc, 0x00, 0x03, 0xc7, 0x8f, 0xb3, 0xcf, 0x1f, 0x42, 0x29, 0xe2, 0x1f, 0x00, 0x00,
    0xef, 0xff, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00,
    0x6f, 0xff, 0xe0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x08, 0x00, 0x00, 0x00, 0x00, 0x1e, 0x00, 0x00};

void OledDisplay::showSplash() {
    _display->drawBitmap(0, 0, epd_bitmap_bs_splash, 128, 32, WHITE);
}
