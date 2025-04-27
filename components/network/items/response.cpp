#include "response.h"

Response::Response(QTcpSocket* client_link, QJsonObject data) {
    this->client_link = client_link;
    this->data = std::move(data);
}
