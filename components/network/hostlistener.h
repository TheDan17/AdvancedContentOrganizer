#ifndef HOSTLISTENER_H
#define HOSTLISTENER_H

#include <string>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "handler/requesthandler.h"

class Host;
class HostListener : public QTcpServer {
    Q_OBJECT
public: // private:
    std::map<std::string, QTcpSocket*> active_conns;
    RequestHandler &requests;
public:
    Host* host; // Грёбанный костыль который разрушает архитектуру
    HostListener(RequestHandler &handler);
    Result<> start_listen();
    std::pair<std::string, int> get_listen_address();
private slots:
    void new_connection();
    void quit_connection();
    void new_request();
};

#endif // HOSTLISTENER_H
