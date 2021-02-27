#ifndef _ONVIF_SERVICE_A_H_
#define _ONVIF_SERVICE_A_H_

#include "onvif_service.h"

class OnvifServiceA : public OnvifService
{
 public:
    OnvifServiceA();
    ~OnvifServiceA();

    virtual int start();

 private:

};


#endif  // _ONVIF_SERVICE_A_H_
