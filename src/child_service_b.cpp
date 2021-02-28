#include "child_service_b.h"

#include <iostream>

ChildServiceB::ChildServiceB() : ParentService("ServiceB")
{
    // std::cout << "Created " << get_client_id() << "..." << std::endl;
}

ChildServiceB::~ChildServiceB()
{
    // std::cout << "Destroyed " << get_client_id() << "..." << std::endl;
}

int ChildServiceB::start()
{
    std::cout << "Started " << get_client_id() << "..." << std::endl;

    m_pMqttClient->subscribe(nullptr, "command/service_b/#");

    ParentService::start();

    return 0;
}
