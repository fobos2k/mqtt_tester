#include "onvif_service.h"

#include <iostream>

OnvifService::OnvifService(std::string id)
{
    m_ClientId = id;

    m_pMqttClient.reset(new mosqpp::mosquittopp(id.c_str()));
}

OnvifService::~OnvifService()
{

}

int OnvifService::init()
{
    std::cout << m_ClientId << ": Init..." << std::endl;

    int rc = mosqpp::lib_init();

    std::cout << m_ClientId << ": MQTT: Connect..." << std::endl;
    rc = m_pMqttClient->connect_async(MQTT_HOST, MQTT_PORT, MQTT_KEEPALIVE);

    if ( rc != MOSQ_ERR_SUCCESS ) {
        std::cout << m_ClientId << ": MQTT: Connection error... (" << rc << ")" << std::endl;
        return rc;
    }

    std::cout << m_ClientId << ": MQTT: Loop start..." << std::endl;
    rc = m_pMqttClient->loop_start();
    if ( rc )
        m_pMqttClient->reconnect_async();
    
    return 0;
}
