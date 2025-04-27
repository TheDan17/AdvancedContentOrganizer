#include "helpers.h"

#include <QString>
std::string Helpers::formatHost(std::string address, int port){
    return QString("%1:%2").arg(address.c_str(), QString::number(port)).toStdString();
}

std::string Helpers::formatConn(QTcpSocket* connection){
    return Helpers::formatHost(connection->peerAddress().toString().toStdString(),
                               connection->peerPort());
}
