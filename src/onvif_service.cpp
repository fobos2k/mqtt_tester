#include "onvif_service.h"

#include <iostream>

OnvifService::OnvifService(std::string id)
{
    m_ClientId = id;
    m_pMqttClient.reset(new mqtt_client(id));
}

OnvifService::~OnvifService()
{
    std::cout << "... destroyed " << m_ClientId << std::endl;
}

int OnvifService::init()
{
    std::cout << m_ClientId << ": Init..." << std::endl;
    m_pMqttClient->init();

    return 0;
}

int OnvifService::start()
{
    std::cout << m_ClientId << ": Start (base)..." << std::endl;

    return 0;
}
