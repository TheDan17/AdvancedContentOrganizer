#include "host.h"

#include "../../main/globalinstances.h"

#include <QMessageBox>

Host::Host() : requests(), responses(), listener(requests) {
    listener.host = this;

    // Для обработки запроса хостом
    QObject::connect(&this->requests, &RequestHandler::need_process_request,
                     this, &Host::processRequest);
    // Для продолжения обработки запросов циклом
    QObject::connect(this, &Host::processRequestEnded,
                     &this->requests, &RequestHandler::request_processed);

    requests.start_processing();
    responses.start_processing();

    // Начать прослушивание сервера
    auto listener_result = this->listener.start_listen();
    if (!listener_result.is_ok()) {
        global::logger()->log_error("Couldn't start server: ", listener_result.error());
    }
}
Host::~Host(){
    requests.stop_processing();
    responses.stop_processing();
}

#include "../../utils/networkjsoncreator.h"
QJsonObject uniteJson(NetworkData net){
    QJsonObject obj;
    obj["head"] = net.head.c_str();
    obj["uuid"] = net.uuid.c_str();
    obj["type"] = "request";
    obj["data"] = net.data;
    return std::move(obj);
}
#include <QInputDialog>
#include "../../utils/helpers.h"
#include "networksender.h"
void Host::processRequest(NetworkData request){
    if (request.head == headers::send_msg){
        emit getMessageFromClient(request.data.value("msg").toString().toStdString());
    }
    if (request.head == headers::try_login){
        std::string login, password;
        login = request.data.value("login").toString().toStdString();
        password = request.data.value("password").toString().toStdString();
        QJsonObject j = uniteJson(request);
        if (login == this->serverName && password == "justuser"){
            j = NetworkJsonCreator::try_login_result(j, true, "success login");
        } else {
            j = NetworkJsonCreator::try_login_result(j, false, "success login");
        }
        network::send_data(request.socket, std::move(j));
        //responses.add_response(Response(request.socket, std::move(j)));
    }
    if (request.head == headers::send_report) {
        // По идее, это должно обрабатываться так: уведомление отсылается в центр, который уже читает View и когда админ сервера кликает, тогда ему отображается репорт и возможность ответить, после чего отправляется команда отправки ответа, где по Uuid клиент поймёт, что это ответ на его тот репорт
        // Таким образом соблюдается иерархия MVC - Model может только изменить состояние, которое прочитает View, Остальное взаимодействие сводится к следующей зависимости: View знает Controller, Controller знает Model.
        QString text = request.data.value("text").toString();
        QString msg = "От клиента с адресом "; // Тут должен быть не адрес, а uuid
        msg += Helpers::formatConn(request.socket);
        msg += " поступил репорт следующего содержания: \n\"";
        msg += text;
        msg += "\"\nВведите текст для отправки ответа на этот репорт: ";
        QString reply = QInputDialog::getText(nullptr, "Получен репорт", msg);
        QJsonObject j = uniteJson(request);
        j = NetworkJsonCreator::reply_report_from_server(j, reply.toStdString());
        network::send_data(request.socket, std::move(j));
    }

    emit processRequestEnded();
}
// Это нужно?
void Host::transferResponse(NetworkData response){
    responses.add_response(response);
}
