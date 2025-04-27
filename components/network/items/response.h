#ifndef RESPONSE_H
#define RESPONSE_H

#include <QTcpSocket>
#include <QJsonObject>

class Response {
public:
    QTcpSocket* client_link;
    QJsonObject data;
    Response(QTcpSocket* client_link, QJsonObject data);
};

#endif // RESPONSE_H
