#include "addserverconnectdialog.h"

AddServerConnectDialog::AddServerConnectDialog(QWidget* parent, View* view) :
        QDialog(parent), ui(new Ui::AddServerConnectDialog) {
    this->ui->setupUi(this);
    this->view = view;
    QObject::connect(this->ui->checkButton, &QPushButton::clicked,
                     this, &AddServerConnectDialog::onCheckClickedButton);
    QObject::connect(this, &AddServerConnectDialog::checkConnectionFinished,
                     this, &AddServerConnectDialog::onConnectionTried);
    QObject::connect(this->ui->nextButton, &QPushButton::clicked, this, &QDialog::accept);
}
AddServerConnectDialog::~AddServerConnectDialog(){
    delete this->ui;
}

void AddServerConnectDialog::fetchData(){
    this->address = this->ui->addressEdit->text().toStdString();
    std::string port_str = this->ui->portEdit->text().toStdString();
    try {
        this->port = std::stoi(port_str);
    } catch (std::invalid_argument e) {
        this->port = -1;
    }
}

#include <QString>
#include <QMessageBox>
#include <QThreadPool>
void AddServerConnectDialog::onCheckClickedButton(){
    this->fetchData();
    ui->signalLabel->setText(QString("🟡"));
    ui->nextButton->setDisabled(true);
    ui->statusLabel->setText("Погодите, ща");

    // MAIN PART
    auto result = this->view->tryConnection(this->address, this->port);
    emit checkConnectionFinished(result);
}
void AddServerConnectDialog::onConnectionTried(Result<> result){
    if (result.is_ok()) {
        ui->signalLabel->setText(QString("🟢"));
        ui->statusLabel->setText("Супер");
        ui->nextButton->setDisabled(false);
    } else {
        ui->signalLabel->setText(QString("🔴"));
        ui->statusLabel->setText("Не работает");
        QMessageBox::critical(this, "Ошибка соединения", result.error().what());
    }
}

std::pair<std::string, int> AddServerConnectDialog::get_ip_port(){
    return std::make_pair(this->address, this->port);
}
