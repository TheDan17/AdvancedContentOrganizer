#ifndef REQUEST_H
#define REQUEST_H

#include <QTcpSocket>
#include <QJsonObject>

class Request {
public:
    QTcpSocket* client_link;
    QJsonObject data;
    Request(QTcpSocket* client_link, QJsonObject data);
};

#endif // REQUEST_H
