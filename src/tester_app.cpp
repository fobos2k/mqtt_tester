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

int TesterApp::start()
{
    std::cout << "App started..." << std::endl;

    std::unique_ptr<OnvifServiceA> service_a(new OnvifServiceA);
    std::unique_ptr<OnvifServiceB> service_b(new OnvifServiceB);

    service_a->init();
    service_b->init();
    
    return 0;
}
