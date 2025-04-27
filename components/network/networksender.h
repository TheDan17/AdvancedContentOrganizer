#ifndef NETWORKSENDER_H
#define NETWORKSENDER_H

#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>

#include "../../utils/resulthandler.h"

class NetworkSender {
public:
    static Result<> send_data(QTcpSocket* socket, QJsonObject data){
        if (socket->state() == QTcpSocket::ClosingState ||
            socket->state() == QTcpSocket::UnconnectedState) {
            return error("Socket is closed(-ing), no way to send data");
        }
        if (socket->state() != QTcpSocket::ConnectedState)
            return error("Socket not connected, try later");

        QJsonDocument parser(data);
        QByteArray send_data = parser.toJson();
        socket->write(send_data);
        socket->flush();
        return value();
    }
};

typedef NetworkSender network;

#endif // NETWORKSENDER_H
