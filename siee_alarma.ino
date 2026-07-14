#include "config.h"
#include "Logger.h"
#include "Display.h"

Display display;

void setup()
{
    Logger::begin();

    Logger::info("Iniciando...");

    if(display.begin())
    {
        Logger::info("Display OK");
    }
    else
    {
        Logger::error("Display NO encontrado");
    }

    display.showStatus("DESARMADA");
}

void loop()
{

}
