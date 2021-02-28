#include "parent_service.h"

#include <iostream>

ParentService::ParentService(std::string id)
{
    m_ClientId = id;
    m_pMqttClient.reset(new mqtt_client(id));
}

ParentService::~ParentService()
{
    std::cout << "... destroyed " << m_ClientId << std::endl;
}

int ParentService::init()
{
    std::cout << m_ClientId << ": Init..." << std::endl;
    m_pMqttClient->init();

    return 0;
}

int ParentService::start()
{
    std::cout << m_ClientId << ": Start (base)..." << std::endl;

    return 0;
}
