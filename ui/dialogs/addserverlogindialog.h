#ifndef ADDSERVERLOGINDIALOG_H
#define ADDSERVERLOGINDIALOG_H

#include <string>
#include <QDialog>

#include "../../ui_addserverlogindialog.h"
#include "../../main/mvc/view.h"

class AddServerLoginDialog : public QDialog {
    Q_OBJECT
private:
    Ui::AddServerLoginDialog *ui;
    View* view;

    std::string identic;
    std::string name;
    std::string password;
    void fetchData();

    bool is_first_server = true;
public:
    explicit AddServerLoginDialog(std::string identic, View* view, QWidget *parent = nullptr);
    ~AddServerLoginDialog();
    std::pair<std::string, std::string> get_name_password();

    enum loginstatus{waiting, success, fail};
    void set_status(enum loginstatus s);
public slots:
    void onCheckClickedButton();
    void getTryLoginResponse(bool is_success, std::string msg);
    void onServerTried(Result<> result);
signals:
    void tryLoginFinished(Result<> result);
};

#endif // ADDSERVERLOGINDIALOG_H
