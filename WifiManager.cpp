#include "WiFiManager.h"
#include "config.h"

WiFiManager::WiFiManager()
{
    _connected = false;
}

bool WiFiManager::begin()
{
    Serial.println();
    Serial.println("Conectando a WiFi...");

    WiFi.mode(WIFI_STA);
    WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

    uint8_t intentos = 0;

    while (WiFi.status() != WL_CONNECTED && intentos < 20)
    {
        delay(500);
        Serial.print(".");
        intentos++;
    }

    if (WiFi.status() == WL_CONNECTED)
    {
        _connected = true;

        Serial.println();
        Serial.println("WiFi conectado");
        Serial.print("IP: ");
        Serial.println(WiFi.localIP());

        return true;
    }

    _connected = false;

    Serial.println();
    Serial.println("No se pudo conectar al WiFi");

    return false;
}

void WiFiManager::update()
{
    _connected = (WiFi.status() == WL_CONNECTED);
}

bool WiFiManager::isConnected() const
{
    return _connected;
}
