#ifndef HELPERS_H
#define HELPERS_H

#include <string>
#include <QTcpSocket>

class Helpers {
public:
    static std::string formatHost(std::string address, int port);
    static std::string formatConn(QTcpSocket* connection);
};

#endif // HELPERS_H
