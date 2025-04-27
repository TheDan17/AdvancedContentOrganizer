#include "client.h"

#include <QMessageBox>

Client::Client() {}
#include "../../utils/helpers.h"
Result<> Client::try_add_connection(std::string address, int port){
    QTcpSocket* socket = new QTcpSocket(this);

    QObject::connect(socket, &QTcpSocket::readyRead, this, &Client::getResponseRaw);
    QObject::connect(this, &Client::RawResponseConverted, this, &Client::getResponse);
    connect(socket, &QTcpSocket::errorOccurred, [](QAbstractSocket::SocketError error){
        QMessageBox::critical(nullptr, "Ошибка сокета клиента",
                              std::string("Код ошибки: "+std::to_string(error)).c_str());
    });

    socket->connectToHost(address.c_str(), port);
    if (socket->waitForConnected(5000)) {
        std::string identic = Helpers::formatHost(address, port);
        this->id_sockets.insert({std::move(identic), socket});
        return value();
    } else {
        socket->deleteLater();
        return error(socket->errorString().toStdString());
    }
}

#include <QJsonDocument>
void Client::getResponseRaw(){
    QMessageBox::information(nullptr, "Отладка", "Вызван сигнал приёма ответа");
    QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
    if (socket){
        QByteArray data = socket->readAll();
        QJsonDocument jsonDoc = QJsonDocument::fromJson(data);

        if (!jsonDoc.isNull() && jsonDoc.isObject()) {
            QJsonObject jsonObj = jsonDoc.object();
            emit RawResponseConverted(new Response(socket, std::move(jsonObj)));
        } else {
            QMessageBox::warning(nullptr, "Нестандартный ответ от хоста", QString::fromUtf8(data));
        }
    }
}

#include "networkconvert.h"
#include "../../utils/networkjsoncreator.h"
void Client::getResponse(Response* response){
    QMessageBox::information(nullptr, "Отладка повторная", "Получен ответ от сервера");
    NetworkData response_data = NetworkConvert::fromResponse(response);

    if (response_data.head == headers::try_login_result) {
        std::string msg = response_data.data.value("msg").toString().toStdString();
        if (response_data.data.value("is_success").toBool() == true) {
            std::string identic = Helpers::formatConn(response_data.socket);
            std::string sname = response_data.data.value("login").toString().toStdString();
            this->sname_id.insert({sname, identic});
            this->id_sname.insert({identic, sname});
            emit tryLoginGettedResponse(true, msg);
        } else {
            emit tryLoginGettedResponse(false, msg);
        }
    } else if (response_data.head == headers::notify) {
        std::string name = id_sname.at(Helpers::formatConn(response->client_link));
        QString title = "Уведомление от '";
        title += name.c_str();
        title += "'";
        QString msg = response_data.data.value("text").toString();
        QMessageBox::information(nullptr, title, msg);
    } else if (response_data.head == headers::reply_report) {
        QString msg = response_data.data.value("text").toString();
        QMessageBox::information(nullptr, "Получен ответ", "Вы получили ответ от сервера, которому вы присылали репорт.\n"+msg);
    } else {
        QJsonDocument doc(response->data);
        QMessageBox::information(nullptr, "Неизвестный заголовок ответа",
                                 doc.toJson(QJsonDocument::Indented));
    }
}
