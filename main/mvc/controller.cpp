#include "controller.h"

Result<> Controller::init_mvc(){
    //this->view = new View(this);
    //auto init_ui_result = view->init_ui();

    //this->model = new Model();
    //auto init_model_result = model->init_model();

    //if (init_ui_result.is_ok() && init_model_result.is_ok())
    //    return value();
    //else
    //    return error("Init mvc failed. For additional info see log.");
}
Result<int> Controller::start(){
    //this->model->start();
    //todo qthread;
    //auto view_result = this->view->start_ui();
    //return value(view_result.value());
}

Result<> Controller::tryConnection(std::string address, int port){
    return this->model->tryConnection(address, port);
}

Result<> Controller::trySendMsgToHostName(std::string server_name, std::string msg){
    return trySendMsgToHost(model->client->sname_id.at(server_name), msg);
}
#include "../../utils/networkjsoncreator.h"
#include "../../components/network/networksender.h"
Result<> Controller::trySendMsgToHost(std::string host_identic, std::string msg){
    QTcpSocket* host = model->client->id_sockets.at(host_identic);
    QJsonObject data = NetworkJsonCreator::send_msg(msg);
    return network::send_data(host, data);
}
Result<> Controller::tryAddServer(std::string identic, std::string name, std::string password){
    if (model->client->id_sockets.find(identic) == model->client->id_sockets.end())
        return error("No such socket");
    QTcpSocket* socket = this->model->client->id_sockets.at(identic);
    QJsonObject data = NetworkJsonCreator::try_login(name, password);
    return network::send_data(socket, data);
}
