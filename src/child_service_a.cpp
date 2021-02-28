#include "child_service_a.h"

#include <iostream>

ChildServiceA::ChildServiceA() : ParentService("ServiceA")
{
    // std::cout << "Created " << get_client_id() << "..." << std::endl;
}

ChildServiceA::~ChildServiceA()
{
    // std::cout << "Destroyed " << get_client_id() << "..." << std::endl;
}

int ChildServiceA::start()
{
    std::cout << "Started " << get_client_id() << "..." << std::endl;

    m_pMqttClient->subscribe(nullptr, "command/service_a/#");

    ParentService::start();

    return 0;
}
