#ifndef CLIENT_H
#define CLIENT_H

#include <string>
#include <map>
#include <QObject>
#include <QTcpSocket>

#include "items/response.h"
#include "items/networkdata.h"
#include "../../utils/resulthandler.h"

class Client : public QObject {
    Q_OBJECT
private:
    //int timeout_seconds = 5;
public:
    std::map <std::string, std::string> sname_id; // ! server name - identic !
    std::map <std::string, std::string> id_sname; // ! identic - server name !
    std::map <std::string, QTcpSocket*> id_sockets; // ! identic - server socket !

    Client();
    Result<> try_add_connection(std::string adress, int port);
public slots:
    void getResponseRaw();
    void getResponse(Response* data);
signals:
    void RawResponseConverted(Response* data);
    void tryLoginGettedResponse(bool is_success, std::string msg);
};

#endif // CLIENT_H
