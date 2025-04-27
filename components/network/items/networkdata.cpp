#include "networkdata.h"

NetworkData::NetworkData(QTcpSocket* s, std::string head, std::string uuid, enum netType t, QJsonObject d) {
    this->socket = s;
    this->head = head;
    this->uuid = uuid;
    this->type = t;
    this->data = d;
}
