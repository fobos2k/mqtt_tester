#include <iostream>
#include <memory>

#include "tester_app.h"
#include "onvif_service_a.h"
#include "onvif_service_b.h"

TesterApp::TesterApp()
{
}

TesterApp::~TesterApp()
{

}

int TesterApp::init()
{
    return 0;
}

int TesterApp::start()
{
    std::cout << "App started..." << std::endl;

    std::unique_ptr<OnvifService> service_a(new OnvifServiceA);
    std::unique_ptr<OnvifService> service_b(new OnvifServiceB);

    if ( service_a->init() == 0 )
        service_a->start();
    
    if ( service_b->init() == 0 )
        service_b->start();

    return 0;
}
