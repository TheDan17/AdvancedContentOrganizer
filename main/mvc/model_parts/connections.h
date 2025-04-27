#ifndef CONNECTIONS_H
#define CONNECTIONS_H

#include <QObject>
#include <QTcpSocket>

#include "../../../utils/resulthandler.h"

class HostListener : public QObject {
    Q_OBJECT
    QTcpSocket qts;
public:
    HostListener();
    Result<std::monostate, int> start_listen_loop(int port);
signals:
    //Result<QTcpSocket*> connection_catched();
};

class Host : public QObject {
    Q_OBJECT
private:
    HostListener hl;
public:
    Host();
    Result<std::monostate, int> start_listen(int port);
public slots:
    //void try_add_connection(Result<QTcpSocket*> conn);
};

class Client {
    Client();
    Result<QTcpSocket*> try_connect_host(std::string ip, int port);
    Result<> try_connect_server(std::string conn_name, std::string login, std::string password);
};

#endif // CONNECTIONS_H
