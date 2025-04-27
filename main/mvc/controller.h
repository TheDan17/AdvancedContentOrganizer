#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QApplication>

#include "model.h"
#include "../../utils/resulthandler.h"

class Controller {
private:

public:
    Model* model;
    Controller(Model* model) : model(model) {};
    Result<> init_mvc(); // ?
    Result<int> start(); // ?

    Result<> tryConnection(std::string address, int port);
    Result<> tryAddServer(std::string identic, std::string name, std::string password);

    std::vector<std::string> getKnownHostsIdentics();
    Result<> trySendMsgToHost(std::string host_identic, std::string msg);
    Result<> trySendMsgToHostName(std::string server_name, std::string msg);
};

#endif // CONTROLLER_H
