#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display
{
public:

    bool begin();

    void showSplash();

   void showStatus(bool armed,
                    bool doorOpen,
                    bool pirActive);
   void showExitDelay(uint8_t seconds);
private:

    Adafruit_SSD1306 _display =
        Adafruit_SSD1306(128,64,&Wire,-1);

};

#endif
