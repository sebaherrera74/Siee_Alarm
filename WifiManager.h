
#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

class WiFiManager
{
public:
    WiFiManager();

    bool begin();
    void update();

    bool isConnected() const;

private:
    bool _connected;
};

#endif
