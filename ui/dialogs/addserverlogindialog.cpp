#include "addserverlogindialog.h"
#include "../../ui_addserverlogindialog.h"

AddServerLoginDialog::AddServerLoginDialog(std::string identic, View* view, QWidget *parent)
    : QDialog(parent), ui(new Ui::AddServerLoginDialog), identic(identic), view(view) {
    ui->setupUi(this);
    QObject::connect(this->ui->checkButton, &QPushButton::clicked,
                     this, &AddServerLoginDialog::onCheckClickedButton);
    QObject::connect(this, &AddServerLoginDialog::tryLoginFinished,
                     this, &AddServerLoginDialog::onServerTried);
    QObject::connect(this->ui->nextButton, &QPushButton::clicked, this, &QDialog::accept);
}

AddServerLoginDialog::~AddServerLoginDialog() {
    delete ui;
}

void AddServerLoginDialog::fetchData(){
    this->name = this->ui->nameEdit->text().toStdString();
    this->password = this->ui->passwordEdit->text().toStdString();
}

void AddServerLoginDialog::set_status(enum loginstatus s){
    switch (s){
    case waiting:
        ui->signalLabel->setText(QString("🟡"));
        ui->statusLabel->setText("Погодите, ща");
        break;
    case success:
        ui->signalLabel->setText(QString("🟢"));
        ui->statusLabel->setText("Супер");
        break;
    case fail:
        ui->signalLabel->setText(QString("🔴"));
        ui->statusLabel->setText("Не работает");
    }
}

#include <QString>
#include <QMessageBox>
#include <QThreadPool>
void AddServerLoginDialog::onCheckClickedButton(){
    this->fetchData();
    ui->nextButton->setDisabled(true);
    set_status(waiting);

    auto result = this->view->sendServerLoginRequest(identic, name, password);
    if (!result.is_ok())
        emit tryLoginFinished(error("Не удалось отправить запрос: "+std::string(result.error().what())));
}
void AddServerLoginDialog::getTryLoginResponse(bool is_success, std::string msg){
    if (is_success)
        emit tryLoginFinished(value());
    else
        emit tryLoginFinished(error(msg.c_str()));
}
void AddServerLoginDialog::onServerTried(Result<> result){
    if (result.is_ok()) {
        set_status(success);
        ui->nextButton->setDisabled(false);
        is_first_server = false;
    } else {
        set_status(fail);
        if (!is_first_server)
            ui->nextButton->setDisabled(false);
        QMessageBox::critical(this, "Ошибка соединения", result.error().what());
    }
}

std::pair<std::string, std::string> AddServerLoginDialog::get_name_password(){
    return std::make_pair(this->name, this->password);
}
