#ifndef NETWORKDATA_H
#define NETWORKDATA_H

#include <string>
#include <QTcpSocket>
#include <QJsonObject>

enum netType {request, response};
class NetworkData {
public:
    QTcpSocket* socket;
    std::string head;
    std::string uuid;
    enum netType type;
    QJsonObject data;
    NetworkData(QTcpSocket* s, std::string head, std::string uuid, enum netType t, QJsonObject d);
};

#endif // NETWORKDATA_H
