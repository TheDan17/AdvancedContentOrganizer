#include "request.h"

Request::Request(QTcpSocket* client_link, QJsonObject data) {
    this->client_link = client_link;
    this->data = std::move(data);
}
