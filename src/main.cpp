#include <iostream>
#include <memory>
#include <thread>

#include <sys/signal.h>
#include <string.h>

#include "tester_app.h"

static bool m_Quit = false;

void signal_handler (int signal)
{
    std::cout << "Got signal: " << strsignal(signal) << std::endl;

    if ( signal == SIGSEGV )
        exit(EXIT_FAILURE);

    m_Quit = true;
}

int main (int argc, char * argv[] )
{
    std::cout << "Hi!" << std::endl;
    std::unique_ptr<TesterApp> app(new TesterApp);

    ::signal(SIGINT,  signal_handler);
    ::signal(SIGQUIT, signal_handler);
    ::signal(SIGTERM, signal_handler);
    ::signal(SIGSEGV, signal_handler);
    ::signal(SIGKILL, signal_handler);

    m_Quit = false;

    if ( app->init() == 0 )
        app->start();

    while ( ! m_Quit )
        std::this_thread::sleep_for(std::chrono::milliseconds(10));

    return EXIT_SUCCESS;
}
