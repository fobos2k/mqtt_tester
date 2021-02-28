#include <iostream>
#include <memory>
#include <thread>

#include <sys/signal.h>
#include <string.h>

#include "tester_app.h"
#include "onvif_service_a.h"
#include "onvif_service_b.h"

static bool m_Quit = false;

void signal_handler (int signal)
{
    std::cout << "Got signal: " << strsignal(signal) << std::endl;

    if ( signal == SIGSEGV )
        exit(EXIT_FAILURE);

    m_Quit = true;
}

TesterApp::TesterApp()
{
    mosqpp::lib_init();
}

TesterApp::~TesterApp()
{
    mosqpp::lib_cleanup();
}

int TesterApp::init()
{
    ::signal(SIGINT,  signal_handler);
    ::signal(SIGQUIT, signal_handler);
    ::signal(SIGTERM, signal_handler);
    ::signal(SIGSEGV, signal_handler);
    ::signal(SIGKILL, signal_handler);

    m_Quit = false;

    return 0;
}

int TesterApp::start()
{
    std::cout << "App started..." << std::endl;

    std::unique_ptr<OnvifService> service_a(new OnvifServiceA);
    std::unique_ptr<OnvifService> service_b(new OnvifServiceB);

    if ( service_a->init() == 0 ) {
        service_a->start();
    }

    if ( service_b->init() == 0 ) {
        service_b->start();
    }

    while ( ! m_Quit )
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    return 0;
}
