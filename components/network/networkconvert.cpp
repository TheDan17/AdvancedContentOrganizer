#include "networkconvert.h"

Response* NetworkConvert::toResponse(NetworkData value){
    QJsonObject obj;
    obj["head"] = value.head.c_str();
    obj["uuid"] = value.uuid.c_str();
    obj["type"] = "response";
    obj["data"] = value.data;
    return new Response(value.socket, obj);
}
NetworkData NetworkConvert::fromResponse(Response* value){
    std::string head = value->data.value("head").toString().toStdString();
    std::string uuid = value->data.value("uuid").toString().toStdString();
    std::string type = value->data.value("type").toString().toStdString();
    enum netType nettype;
    if (type == "request")
        nettype = request;
    else
        nettype = response;
    QJsonObject data = value->data.value("data").toObject();
    NetworkData netdata(value->client_link, head, uuid, nettype, data);
    return std::move(netdata);
}

NetworkData NetworkConvert::fromRequest(Request* value){
    std::string head = value->data.value("head").toString().toStdString();
    std::string uuid = value->data.value("uuid").toString().toStdString();
    std::string type = value->data.value("type").toString().toStdString();
    enum netType nettype;
    if (type == "request")
        nettype = request;
    else
        nettype = response;
    QJsonObject data = value->data.value("data").toObject();
    NetworkData netdata(value->client_link, head, uuid, nettype, data);
    return std::move(netdata);
}
