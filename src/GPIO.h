#ifndef __GPIO_H
#define __GPIO_H

#include "Debounce.h"

class GPIOmonitor {
   public:
    GPIOmonitor();
    void setup();
    void loop();

    bool ison_shorePower() { return !_shorePower.read(); }
    bool ison_bilgePump() { return _bilgePump.read(); }
    int32_t battery1() { return _bat1; }
    int32_t battery2() { return _bat2; }

    void toJSON(JSONWriter* json);

   private:
    uint32_t convertADCtoV100(uint32_t v);

   private:
    Debounce _shorePower;
    Debounce _bilgePump;
    int32_t _bat1;
    int32_t _bat2;
};

#endif  // __GPIO_H