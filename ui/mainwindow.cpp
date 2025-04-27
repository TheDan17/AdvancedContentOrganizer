#include "mainwindow.h"

#include <QObject>
#include <QMessageBox>

#include "../utils/strdict.h"

MainWindow::MainWindow(View* view, QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    this->view = view;
    ui->setupUi(this);
    QObject::connect(this, &MainWindow::addServerTriggered,
                     this, &MainWindow::tryConnectServer);
    setWindowTitle(StrDict::Info::AppName.c_str());
}

MainWindow::~MainWindow() {
    delete ui;
}

#include "dialogs/addserverconnectdialog.h"
#include "dialogs/addserverlogindialog.h"
#include "../utils/helpers.h"
void MainWindow::tryConnectServer(){
    auto connectHostDialog = new AddServerConnectDialog(nullptr, this->view);

    auto connectDialogResult = connectHostDialog->exec();
    if (connectDialogResult == QDialog::Rejected)
        return;

    auto host_data = connectHostDialog->get_ip_port();
    std::string identic = Helpers::formatHost(host_data.first, host_data.second);
    auto connectServerDialog = new AddServerLoginDialog(identic, view, this);
    QObject::connect(this->view->c->model->client, &Client::tryLoginGettedResponse,
                     connectServerDialog, &AddServerLoginDialog::getTryLoginResponse);

    connectDialogResult = connectServerDialog->exec();
    if (connectDialogResult == QDialog::Rejected)
        return;

    delete connectHostDialog;
    delete connectServerDialog;
    QMessageBox::information(this, "Уведомление", "Сервер(-а) успешно добавлен в список!");
}


void MainWindow::on_action_9_triggered() {
    int port = this->view->c->model->host->listener.get_listen_address().second;
    std::string msg;
    if (port == 0)
        msg = "Порт: ошибка";
    else
        msg = "Порт: " + std::to_string(port);
    QMessageBox::information(this, "Данные для подключения", msg.c_str());
}

void MainWindow::on_action_17_triggered() { // Клиент - Подключиться к серверу
    emit addServerTriggered();
}
void MainWindow::on_serversAddButton_clicked() {
    emit addServerTriggered();
}
void MainWindow::on_serverAddButton_clicked() {
    emit addServerTriggered();
}
#include <QStringList>
void MainWindow::on_serversRefresh_clicked() {
    QMessageBox::information(this, "Отладка", "Обновляем список серверов");
    auto& m = this->view->c->model->client->sname_id;
    QStringList items;
    for (const auto& [key, _] : m)
        items.append(QString::fromStdString(key));
    ui->serversSelectorCombo->clear();
    ui->serversSelectorCombo->addItems(items);
}

#include <QInputDialog>
void MainWindow::on_action_21_triggered() { // Сервер - Задать имя сервера
    QString msg ("Текущее имя сервера: '");
    msg += view->c->model->host->serverName.c_str();
    msg += "'\nВведите новое его название:";
    bool is_ok_pressed;
    std::string newname = QInputDialog::getText(this, "Изменение имени", msg, QLineEdit::Normal, "", &is_ok_pressed).toStdString();
    if (is_ok_pressed) {
        if (newname.empty())
            QMessageBox::information(this, "Уведомление", "Имя сервера осталось без изменений");
        else
            this->view->c->model->host->serverName = newname;
    }
}
#include <QString>
void MainWindow::on_action_10_triggered() { // Сервер - Показать список подключений
    std::map<std::string, QTcpSocket*>& m = this->view->c->model->host->listener.active_conns;
    QString keys = "Активные подключения:\n";
    if (m.empty())
        keys += "Отсутствуют\n";
    else
        for (const auto& [key, _] : m)
            keys += QString::fromStdString(key) + "\n";
    keys.chop(1);
    QMessageBox::information(this, "Справка от вашего сервера", keys);
}

#include "dialogs/additemtoserverdialog.h"
void MainWindow::on_addButton_clicked() {
    auto dialog = new AddItemToServerDialog(view->c->model->host->serverName,
                                            view->c->model->get_dir_items(),
                                            this);
    auto dresult = dialog->exec();
    if (dresult == QDialog::Rejected)
        return;
    auto itemData = dialog->getData();
    auto result = view->c->model->tryAddToDatabase(itemData);
    QString msg;
    if (result.is_ok()) {
        msg = "Предмет успешно добавлен на сервер '"+itemData.addServer+"'";
        QMessageBox::information(this, "Добавление предмета", msg);
    } else {
        msg = "Во время добавления предмета произошла ошибка: '";
        msg += result.error().what();
        msg += "'";
        QMessageBox::warning(this, "Добавление предмета", msg);
    }
    delete dialog;
}

#include "dialogs/watchdbdialog.h"
void MainWindow::on_action_5_triggered() { // Отладка - Показать таблицы БД
    auto dialog = new WatchDBDialog(this, view, view->c->model->getDBTableNames());
    dialog->exec();
    delete dialog;
}
#include <QInputDialog>
#include "../components/network/networksender.h"
#include "../utils/networkjsoncreator.h"
void MainWindow::on_action_7_triggered() { // Отладка - Отправить уведомление клиентам
    QString text = QInputDialog::getText(this, "Отправка уведомления клиентам", "Введите текст уведомления: ");
    auto special_response = NetworkJsonCreator::notify_client(text.toStdString());
    for (auto& id_socket : view->c->model->host->listener.active_conns){
        network::send_data(id_socket.second, special_response);
    }
    QMessageBox::information(this, "Успешно", "Уведомление клиентов завершено");
}

void MainWindow::on_action_11_triggered() { // Отладка - Отправить репорт серверу
    auto& m = this->view->c->model->client->id_sockets;
    QStringList items;
    for (const auto& [key, _] : m)
        items.append(QString::fromStdString(key));
    QString servername = QInputDialog::getItem(this, "Отправка репорта", "Выберите сервер для отправки репорта:", items);
    QString text = QInputDialog::getText(this, "Отправка репорта", "Введите текст репорта серверу:");
    QJsonObject obj = NetworkJsonCreator::send_report_from_client(text.toStdString());
    QTcpSocket* socket = this->view->c->model->client->id_sockets.at(servername.toStdString());
    //Request req (socket, std::move(obj)); Ох уж эта несогласованная система на костылях
    network::send_data(socket, std::move(obj));
}


// Небольшие планы:
// Каждый клиент имеет свой uuid
// Идентификация происходит по нему, а не по сокету
// Соответственно, уведомление приходит ему в центр уведомлений как только соединение сообщит такой же uuid
// Только после этого уведомление на отправку исчезнет из стека сервера

// Небольшая заметка:
// Каждый хост будет также иметь свой uuid
// В бд будет вестись реест серверов, в котором вместо флага принадлежности это будет определяться как раз по uuid
// Этим ходом заодно решается проблема распознавания своего сервера при работе нескольких программ на одном компьютере
