#ifndef _ONVIF_SERVICE_H_
#define _ONVIF_SERVICE_H_

#include <memory>
#include <string>

#include "mosquittopp.h"

// class mosquittop;

#define MQTT_HOST           "localhost"
#define MQTT_PORT           1883
#define MQTT_KEEPALIVE      60

class OnvifService
{
 public:
    OnvifService(std::string id);
    ~OnvifService();

    std::string get_client_id() { return m_ClientId; }

    int init();

 private:
    std::string m_ClientId = "mqtt_general_client";

    std::unique_ptr<mosqpp::mosquittopp> m_pMqttClient;

};


#endif  // _ONVIF_SERVICE_H_
