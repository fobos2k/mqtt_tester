#include <iostream>
#include <memory>

#include "tester_app.h"

int main (int argc, char * argv[] )
{
    std::cout << "Hi!" << std::endl;
    std::unique_ptr<TesterApp> app(new TesterApp);

    if ( app->init() == 0 )
        app->start();

    return EXIT_SUCCESS;
}
