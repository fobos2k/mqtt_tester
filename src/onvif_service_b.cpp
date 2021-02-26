#include "onvif_service_b.h"

#include <iostream>

OnvifServiceB::OnvifServiceB() : OnvifService("ServiceB")
{
    std::cout << "Created " << get_client_id() << "..." << std::endl;
}

OnvifServiceB::~OnvifServiceB()
{
    std::cout << "Destroyed " << get_client_id() << "..." << std::endl;
}
