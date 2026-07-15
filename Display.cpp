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
    _display.print("Alarm");

    _display.display();
}

void Display::showStatus(bool armed,
                         bool doorOpen,
                         bool pirActive)
{
    _display.clearDisplay();

    _display.setTextColor(SSD1306_WHITE);

    _display.setTextSize(1);
    _display.setCursor(22,0);
    _display.println("SIEE Alarm");
  
   // Línea separadora
  _display.drawLine(0, 10, 127, 10, SSD1306_WHITE);

    _display.setCursor(0,15);

_display.print("Estado : ");

if (armed)
    _display.println("ARMADA");
else
    _display.println("DESARMADA");

_display.println();

_display.print("Puerta : ");

if (doorOpen)
    _display.println("ABIERTA");
else
    _display.println("CERRADA");

_display.print("PIR    : ");

if (pirActive)
    _display.println("ACTIVO");
else
    _display.println("NORMAL");

    _display.display();
}

void Display::showExitDelay(uint8_t seconds)
{
    _display.clearDisplay();

    _display.setTextColor(SSD1306_WHITE);

    _display.setTextSize(1);
    _display.setCursor(22,0);
    _display.println("SIEE Alarm");

    _display.drawLine(0,10,127,10,SSD1306_WHITE);

    _display.setTextSize(2);

    _display.setTextSize(2);
_display.setCursor(8,18);
_display.println("ARMANDO");

_display.setTextSize(3);

if (seconds < 10)
    _display.setCursor(52,40);
else
    _display.setCursor(42,40);

_display.println(seconds);

    _display.display();
}
