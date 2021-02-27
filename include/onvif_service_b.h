#ifndef _ONVIF_SERVICE_B_H_
#define _ONVIF_SERVICE_B_H_

#include "onvif_service.h"

class OnvifServiceB : public OnvifService
{
 public:
    OnvifServiceB();
    ~OnvifServiceB();

    virtual int start();

 private:

};


#endif  // _ONVIF_SERVICE_B_H_
