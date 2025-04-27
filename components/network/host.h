#ifndef HOST_H
#define HOST_H

#include <QObject>

#include "hostlistener.h"
#include "items/networkdata.h"
#include "handler/requesthandler.h"
#include "handler/responsehandler.h"

class Host : public QObject {
    Q_OBJECT
private:
    RequestHandler requests;
    ResponseHandler responses;
public:
    std::string serverName = "server";
    HostListener listener;
    Host();
    ~Host();
public slots:
    void processRequest(NetworkData request);
    void transferResponse(NetworkData response);
signals:
    void processRequestEnded(); // to RequestHandler
    void getMessageFromClient(std::string msg); // to View
};

#endif // HOST_H
