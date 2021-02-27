#include "onvif_service.h"

#include <iostream>

OnvifService::OnvifService(std::string id)
{
    m_ClientId = id;

    m_pMqttClient.reset(new mqtt_client(id));
}

OnvifService::~OnvifService()
{

}

int OnvifService::init()
{
    std::cout << m_ClientId << ": Init..." << std::endl;
    m_pMqttClient->init();

    return 0;
}

int OnvifService::start()
{
    std::cout << "Started (base) " << get_client_id() << "..." << std::endl;
    return 0;
}
