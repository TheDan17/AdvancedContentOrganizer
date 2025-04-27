#include "responsehandler.h"

#include <QTcpSocket>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

#include <QMessageBox>
ResponseHandler::ResponseHandler() : QObject(nullptr), BaseHandler<Response>() {}
Result<> ResponseHandler::process_elem(Response elem){
    //QMessageBox::information(nullptr, "ОТЛАДКА БАЛ БЛА", "ООТПАВЛЯЕМ ОТВЕТ ДЛЯ КЛПЕНТА");
    QJsonDocument parser(elem.data);
    QByteArray send_data = parser.toJson();
    QTcpSocket* client_socket = elem.client_link;
    if (!client_socket->isOpen())
        return error("Cannot send response with closed socket");
    elem.client_link->write(send_data);
    elem.client_link->flush();
    return value();
}

void ResponseHandler::add_response(NetworkData response){
    QJsonObject send_data;
    send_data["head"] = response.head.c_str();
    send_data["uuid"] = response.uuid.c_str();
    send_data["type"] = "response";
    send_data["data"] = response.data;
    Response send_response(response.socket, send_data);
    this->add_new_elem(std::move(send_response));
}
void ResponseHandler::add_response(Response response){
    this->add_new_elem(std::move(response));
}
