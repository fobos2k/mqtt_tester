#ifndef _MQTT_CLIENT_H_
#define _MQTT_CLIENT_H_

#include <string>

#include "mosquittopp.h"

class mqtt_client : public mosqpp::mosquittopp
{
 public:
    mqtt_client(std::string id);
    ~mqtt_client();

    int init();
   
 private:
    std::string m_ClientId = "mqtt_client_general";

    std::string get_log_level(int level);

    void on_connect(int rc);    
    void on_disconnect(int rc);
	void on_publish(int mid);
	void on_message(const struct mosquitto_message * message);
	void on_subscribe(int mid, int qos_count, const int * granted_qos);
	void on_unsubscribe(int mid);
	void on_log(int level, const char * str);
	void on_error();
};


#endif  // _MQTT_CLIENT_H_
