#ifndef ADDSERVERCONNECTIONDIALOG_H
#define ADDSERVERCONNECTIONDIALOG_H

#include <string>
#include <QDialog>

#include "../../ui_addserverconnectdialog.h"
#include "../../main/mvc/view.h"

class AddServerConnectDialog : public QDialog {
    Q_OBJECT
private:
    Ui::AddServerConnectDialog* ui;
    View* view;

    std::string address;
    int port;
    void fetchData();
public:
    AddServerConnectDialog(QWidget* parent, View* view);
    ~AddServerConnectDialog();
    std::pair<std::string, int> get_ip_port();
private slots:
    void onCheckClickedButton();
    void onConnectionTried(Result<> result);
signals:
    void checkConnectionFinished(Result<> result);
};

#endif // ADDSERVERCONNECTIONDIALOG_H
