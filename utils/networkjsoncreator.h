#ifndef NETWORKJSONCREATOR_H
#define NETWORKJSONCREATOR_H

#include <string>
#include <QJsonObject>

class NetworkHeadValues {
public:
    static constexpr const char* check_online = "REQUIRED_CONFIRM";
    static constexpr const char* confirm_online = "CONFIRMED";
    static constexpr const char* notify = "NOTIFY";
    static constexpr const char* send_report = "REPORT";
    static constexpr const char* reply_report = "REPORT";
    static constexpr const char* try_login = "TRY_LOGIN";
    static constexpr const char* try_login_result = "TRY_LOGIN";
    static constexpr const char* send_msg = "SEND_MSG";
    static constexpr const char* reply_msg = "REPLY_MSG";
};
typedef NetworkHeadValues headers;

class NetworkJsonCreator {
public:
    static QJsonObject check_online();
    static QJsonObject confirm_online(QJsonObject& sended_req);
    static QJsonObject notify_client(std::string text);
    static QJsonObject send_report_from_client(std::string report_text);
    static QJsonObject reply_report_from_server(QJsonObject& report, std::string reply_text);
    static QJsonObject try_login(std::string login, std::string password);
    static QJsonObject try_login_result(QJsonObject& sended_req, bool is_success, std::string msg);
    static QJsonObject send_msg(std::string msg);
    static QJsonObject reply_msg(std::string msg, QJsonObject& sended_msg);
};

#endif // NETWORKJSONCREATOR_H
