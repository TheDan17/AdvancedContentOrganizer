#include "requesthandler.h"

#include <string>

RequestHandler::RequestHandler() : QObject(nullptr), BaseHandler<Request>() {
    this->isExternalProcessElem = true;
}
Result<> RequestHandler::process_elem(Request elem){
    std::string head = elem.data["head"].toString().toStdString();
    std::string uuid = elem.data["uuid"].toString().toStdString();
    enum netType type;
    std::string type_str = elem.data["type"].toString().toStdString();
    if (type_str == "request")
        type = request;
    else
        type = response;
    QJsonObject data = elem.data["data"].toObject();
    NetworkData request(elem.client_link, head, uuid, type, data);
    emit need_process_request(std::move(request));
    return value();
}
void RequestHandler::request_processed(){
    this->processCondition.notify_one();
}
