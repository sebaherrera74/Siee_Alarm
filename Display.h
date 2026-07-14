#ifndef DISPLAY_H
#define DISPLAY_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class Display
{
public:

    bool begin();

    void showSplash();

    void showStatus(const char *status);

private:

    Adafruit_SSD1306 _display =
        Adafruit_SSD1306(128,64,&Wire,-1);

};

#endif
