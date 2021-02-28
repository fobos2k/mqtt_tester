#ifndef _PARENT_SERVICE_H_
#define _PARENT_SERVICE_H_

#include <memory>
#include <string>

#include "mqtt_client.h"

class ParentService
{
 public:
    ParentService(std::string id);
    ~ParentService();

    std::string get_client_id() { return m_ClientId; }

    int init();
    virtual int start();

 private:
    std::string m_ClientId = "mqtt_general_client";

 protected:
    std::unique_ptr<mqtt_client> m_pMqttClient;
};


#endif  // _PARENT_SERVICE_H_
