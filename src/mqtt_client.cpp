#include "mqtt_client.h"

#include <iostream>

#define MQTT_HOST           "localhost"
#define MQTT_PORT           1883
#define MQTT_KEEPALIVE      60

mqtt_client::mqtt_client(std::string id) : mosquittopp(id.c_str())
{
    m_ClientId = id;
}

mqtt_client::~mqtt_client()
{

}

std::string mqtt_client::get_log_level(int level)
{
    switch(level) {
    case (1<<0):
        return "I";
    case (1<<1):
        return "N";
    case (1<<2):
        return "W";
    case (1<<3):
        return "E";
    case (1<<4):
        return "D";
    case (1<<5):
        return "S";
    case (1<<6):
        return "U";
    case (1<<7):
        return "B";
    default:
        return "";
    }
}

int mqtt_client::init()
{
    // std::cout << m_ClientId << ": MQTT: Connect..." << std::endl;
    int rc = connect_async(MQTT_HOST, MQTT_PORT, MQTT_KEEPALIVE);

    if ( rc != MOSQ_ERR_SUCCESS ) {
        std::cout << m_ClientId << ": MQTT: Connection error... (" << rc << ")" << std::endl;
        return rc;
    }

    rc = loop_start();
    if ( rc )
        reconnect_async();

    return rc;
}

void mqtt_client::on_connect(int rc)
{
    std::cout << m_ClientId << ": connected (" << rc << ")" << std::endl;
}

void mqtt_client::on_disconnect(int rc)
{
    std::cout << m_ClientId << ": disconnected (" << rc << ")" << std::endl;
}

void mqtt_client::on_publish(int mid)
{
    std::cout << m_ClientId << ": published (" << mid << ")" << std::endl;
}

void mqtt_client::on_message(const struct mosquitto_message * message)
{
    if ( ! message )
        return;

    std::string topic = std::string(message->topic);
    std::string payload = message->payloadlen == 0 ? "" : std::string((char *)message->payload);

    std::cout << m_ClientId << ": received message:" << std::endl
              << "    ->   topic: " << topic << std::endl
              << "    -> payload: " << payload << std::endl;
}

void mqtt_client::on_subscribe(int mid, int qos_count, const int * granted_qos)
{
    std::cout << m_ClientId << ": subscribed (" << mid << ")" << std::endl;
}

void mqtt_client::on_unsubscribe(int mid)
{
    std::cout << m_ClientId << ": unsubscribed (" << mid << ")" << std::endl;
}

void mqtt_client::on_log(int level, const char * str)
{
    std::cout << m_ClientId << ": log (" << get_log_level(level) << "): " << std::string(str) << std::endl;
}

void mqtt_client::on_error()
{

}
