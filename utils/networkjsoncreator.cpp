#include "networkjsoncreator.h"

#include <QUuid>

#include <algorithm>
typedef enum jsontype {REQUEST, RESPONSE} jsontype;
QJsonObject get_template(std::string head, jsontype type, std::string uuid = ""){
    QJsonObject obj;
    // Head
    for (auto& c: head) c = std::toupper(c);
    obj["head"] = head.c_str();
    // Uuid
    if (uuid.empty())
        uuid = QUuid::createUuid().toString().toStdString().c_str();
    obj["uuid"] = uuid.c_str();
    // Type
    if (type == REQUEST)
        obj["type"] = "request";
    else
        obj["type"] = "response";
    // Data
    obj["data"] = QJsonObject();
    return std::move(obj);
}
std::string extract_uuid(QJsonObject& obj){
    return obj.value("uuid").toString().toStdString();
}

QJsonObject NetworkJsonCreator::check_online(){
    return std::move(get_template(headers::check_online, REQUEST));
}
QJsonObject NetworkJsonCreator::confirm_online(QJsonObject& sended_req){
    return std::move(get_template(headers::confirm_online, RESPONSE, extract_uuid(sended_req)));
}

QJsonObject NetworkJsonCreator::notify_client(std::string text){
    QJsonObject obj = get_template(headers::notify, RESPONSE);
    QJsonObject data; data["text"] = text.c_str();
    obj["data"] = data;
    return std::move(obj);
}

QJsonObject NetworkJsonCreator::send_report_from_client(std::string report_text){
    QJsonObject obj = get_template(headers::send_report, REQUEST);
    QJsonObject data; data["text"] = report_text.c_str();
    obj["data"] = data;
    return std::move(obj);
}
QJsonObject NetworkJsonCreator::reply_report_from_server(QJsonObject& report, std::string reply_text){
    QJsonObject obj = get_template(headers::reply_report, RESPONSE, extract_uuid(report));
    QJsonObject data; data["text"] = reply_text.c_str();
    obj["data"] = data;
    return std::move(obj);
} // Стоит ли придумать какую-то краткую элегантную конструкцию для объединения дублирующегося кода?

QJsonObject NetworkJsonCreator::try_login(std::string login, std::string password){
    QJsonObject obj = get_template(headers::try_login, REQUEST);
    QJsonObject data;
    data["login"] = login.c_str();
    data["password"] = password.c_str();
    obj["data"] = data;
    return std::move(obj);
}
QJsonObject NetworkJsonCreator::try_login_result(QJsonObject& sended_req, bool is_success, std::string msg){
    QJsonObject obj = get_template(headers::try_login, RESPONSE, extract_uuid(sended_req));
    QJsonObject data;
    data["is_success"] = is_success;
    data["msg"] = msg.c_str();
    data["login"] = sended_req.value("data").toObject().value("login").toString();
    data["password"] = sended_req.value("data").toObject().value("password").toString();
    obj["data"] = data;
    return std::move(obj);
}

QJsonObject NetworkJsonCreator::send_msg(std::string msg){
    QJsonObject obj = get_template(headers::send_msg, REQUEST);
    QJsonObject data; data["msg"] = msg.c_str();
    obj["data"] = data;
    return std::move(obj);
}
QJsonObject NetworkJsonCreator::reply_msg(std::string msg, QJsonObject& sended_msg){
    QJsonObject obj = get_template(headers::reply_msg, REQUEST, extract_uuid(sended_msg));
    QJsonObject data; data["msg"] = msg.c_str();
    obj["data"] = data;
    return std::move(obj);
}
