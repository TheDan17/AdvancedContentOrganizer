#include "view.h"

#include <QString>

#include "../../utils/strdict.h"
#include "../globalinstances.h"

View::View(Controller* c) {
    this->c = c;
}

Result<> View::init_ui(){
    this->main_window = new MainWindow(this);
    global::logger()->log_msg(INFO, "MainWindow created.");

    return value();
}
Result<int> View::start_qloop(){
    global::logger()->log_msg(INFO, "Try show main window.", typeid(*this).name());
    this->main_window->show();

    global::logger()->log_msg(INFO, "Start app.exec()", typeid(*this).name());
    int app_result = QApplication::instance()->exec();

    global::logger()->log_msg(DEBUG, "App.exec() is done. Return code: " + std::to_string(app_result));
    return value(app_result);
}


#include "controller.h"
Result<> View::tryConnection(std::string address, int port){
    return this->c->tryConnection(address, port);
}
Result<> View::sendServerLoginRequest(std::string identic, std::string name, std::string password){
    return this->c->tryAddServer(identic, name, password);
}
