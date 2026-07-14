#include "Display.h"
#include "config.h"
#include <Wire.h>

bool Display::begin()
{
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!_display.begin(SSD1306_SWITCHCAPVCC, OLED_ADDRESS))
        return false;

    _display.setRotation(2);      // Gira la pantalla 180°
    _display.clearDisplay();
    _display.display();

    return true;
}
void Display::showSplash()
{
    _display.clearDisplay();

    _display.setTextSize(2);
    _display.setCursor(5,5);
    _display.println("SIEE");

    _display.setTextSize(1);
    _display.println("Alarm");

    _display.display();
}

void Display::showStatus(const char *status)
{
    _display.clearDisplay();

    _display.setTextColor(SSD1306_WHITE);
    _display.setTextSize(2);
    _display.setCursor(0,0);

    _display.println(status);

    _display.display();
}
