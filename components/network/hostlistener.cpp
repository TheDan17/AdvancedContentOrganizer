#include "hostlistener.h"

#include "../../utils/helpers.h"

HostListener::HostListener(RequestHandler &handler) : QTcpServer(nullptr), requests(handler){
    QObject::connect(this, &QTcpServer::newConnection, this, &HostListener::new_connection);
}
Result<> HostListener::start_listen(){
    if (this->listen(QHostAddress::Any, 0)){
        return value();
    } else {
        return error(this->errorString().toStdString());
    }
}

std::pair<std::string, int> HostListener::get_listen_address(){
    return {this->serverAddress().toString().toStdString(), this->serverPort()};
}

#include <QThread>
#include <QMessageBox>
#include <QTimer>
void HostListener::new_connection(){
    QMessageBox::information(nullptr, "Отладка", "Обработка нового подключения в слоте");
    QTcpSocket* new_socket = this->nextPendingConnection();
    if (!new_socket) {
        QMessageBox::critical(nullptr, "Ошибка", "nextPendingConnection() вернул nullptr");
        return;
    }
    QObject::connect(new_socket, &QTcpSocket::disconnected, this, &HostListener::quit_connection);
    QObject::connect(new_socket, &QTcpSocket::readyRead, this, &HostListener::new_request);
    connect(new_socket, &QTcpSocket::errorOccurred, [](QAbstractSocket::SocketError error){
        QMessageBox::critical(nullptr, "Ошибка в хосте", std::to_string(error).c_str());
    });
    std::string socket_id = Helpers::formatConn(new_socket);
    this->active_conns.insert({socket_id, new_socket});
}

void HostListener::quit_connection(){
    QMessageBox::information(nullptr, "Отладка", "Подключение от клиента разорвалось");
    QTcpSocket* quit_socket = qobject_cast<QTcpSocket*>(sender());
    if (!quit_socket)
        return;
    this->active_conns.erase(Helpers::formatConn(quit_socket));
    quit_socket->deleteLater();
}

#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include "networksender.h"
#include "networkconvert.h"
#include "host.h"
void HostListener::new_request(){
    QMessageBox::information(nullptr, "Отладка", "Получен сигнал о запросе от клиента");
    QTcpSocket* request_socket = qobject_cast<QTcpSocket*>(sender());
    if (!request_socket)
        return;
    QByteArray socket_data = request_socket->readAll();
    QJsonDocument parser = QJsonDocument::fromJson(socket_data);
    if (!parser.isObject())
        return;
    QJsonObject request_data = parser.object();
    Request request_obj(request_socket, request_data);
    this->host->processRequest(std::move(NetworkConvert::fromRequest(&request_obj)));
    // Боже костыль уже сделанный после системы которая должна была работать.
    //this->requests.add_new_elem(std::move(request_obj));

}
