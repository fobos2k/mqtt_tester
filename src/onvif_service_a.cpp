#include "onvif_service_a.h"

#include <iostream>

OnvifServiceA::OnvifServiceA() : OnvifService("ServiceA")
{
    std::cout << "Created " << get_client_id() << "..." << std::endl;
}

OnvifServiceA::~OnvifServiceA()
{
    std::cout << "Destroyed " << get_client_id() << "..." << std::endl;
}
