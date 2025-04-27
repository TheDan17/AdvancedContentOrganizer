#ifndef VIEW_H
#define VIEW_H

#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QMessageBox>

#include "controller.h"
#include "../../ui/mainwindow.h"
#include "../../utils/resulthandler.h"

class View : public QWidget {
    Q_OBJECT
private:
    MainWindow* main_window;
public:
    Controller* c;
    View(Controller* c);
    Result<> init_ui();
    Result<int> start_qloop();

    Result<> tryConnection(std::string address, int port);
    Result<> sendServerLoginRequest(std::string identic, std::string name, std::string password);

    std::vector<std::string> getKnownHostsIdentics(){ return c->getKnownHostsIdentics(); };
    Result<> trySendMsgToHost(std::string host_identic, std::string msg){ return c->trySendMsgToHost(host_identic, msg); }
public slots:
    void receivedMsg(std::string msg){QMessageBox::information(this, "Сообщение", msg.c_str());};
};

#endif // VIEW_H
