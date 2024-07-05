#ifndef __OledDisplay_h
#define __OledDisplay_h

class OledWingAdafruit;

class OledDisplay {
   public:
    OledDisplay();
    virtual ~OledDisplay();
    void setup();
    void loop();
    void clear(u_int8_t size);
    size_t println(const char* buf);
    void showSplash();
    void display();

   private:
    OledWingAdafruit* _display;
};

#endif  // def(__OledDisplay_h)