#ifndef __TIMER_H
#define __TIMER_H

class MilliTimer {
   public:
    MilliTimer(system_tick_t period) : _period(period), _last(0) {}
    bool timeout() {
        if (millis() - _last < _period) return false;
        _last = millis();
        return true;
    }
    system_tick_t remaining() { return _period - (millis() - _last); }

   private:
    system_tick_t _period;
    system_tick_t _last;
};

#endif