#include "model.h"

Model::Model() {}
Result<> Model::init_model(){
    this->host = new Host();
    this->client = new Client();
    return value();
}

Result<> Model::tryConnection(std::string address, int port){
    return this->client->try_add_connection(address, port);
}

#include "../globalinstances.h"
QString get_item_dir_query = "SELECT id, name FROM items_data WHERE kind = 'DIRECTORY';";
std::vector<std::pair<int, std::string>> Model::get_dir_items(){
    QSqlQuery q; q.prepare(get_item_dir_query);
    auto result = global::dbrel()->action->execQuery(std::move(q), false);

    std::vector<std::pair<int, std::string>> items = {{0, "root"}};
    if (result.is_ok()){
        auto rows = result.value();
        for (auto& item : rows)
            items.push_back(std::make_pair(item.value(0).toInt(), item.value(1).toString().toStdString()));
    }
    return std::move(items);
}

#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>
#include <QFileInfo>
QString add_item_data_query = "INSERT INTO items_data (id, name, kind, parent_item, location, destination) VALUES (:id, :name, :kind, :parent_item, :location, :destination);";
// TODO get id from coordination table in db
QString get_max_id_query = "SELECT MAX(id) FROM items_data;";
Result<> Model::tryAddToDatabase(addItemData itemData){
    QSqlQuery addquery;
    if (!addquery.prepare(add_item_data_query)){
        QMessageBox::information(nullptr, "ОШИБКА", addquery.lastError().text());
    }
    if (itemData.addType == noneType)
        return error("type is none");
    if (itemData.addType == dir && itemData.addStorage != noneStorage) // TODO delete
        return error("dir can't have path");

    // ID
    int maxId = 0;
    QSqlQuery q(get_max_id_query);
    if (q.next())
        maxId = q.value(0).toInt();
    addquery.bindValue(":id", maxId+1);
    // NAME & PATH
    if (itemData.addType == dir) {
        addquery.bindValue(":name", itemData.addPath);
        addquery.bindValue(":destination", "");
    } else {
        if (itemData.addStorage == cloud){
            addquery.bindValue(":name", "сетевой файл");
            addquery.bindValue(":destination", itemData.addPath);
        } else {
            QFileInfo fileinfo (itemData.addPath);
            if (fileinfo.exists()) {
                addquery.bindValue(":name", fileinfo.fileName());
                addquery.bindValue(":destination", fileinfo.absolutePath());
            } else {
                addquery.bindValue(":name", itemData.addPath);
                addquery.bindValue(":destination", "not exist");
            }
        }
    }
    // TYPE
    if (itemData.addType == file)
        addquery.bindValue(":kind", "FILE");
    else
        addquery.bindValue(":kind", "DIRECTORY");
    // PARENT ID
    addquery.bindValue(":parent_item", itemData.addParent);
    // STORAGE.
    if (itemData.addStorage == disk)
        addquery.bindValue(":location", "DISK");
    else
        addquery.bindValue(":location", "CLOUD");

    auto result = global::dbrel()->action->execQuery(std::move(addquery), false);
    if (result.is_ok())
        return value();
    else
        return error(result.error().what());
}

#include <QString>
#include "../../components/database/strategies/mysql/dbrelcontrolmysql.h"
QStringList Model::getDBTableNames(){
    auto& tablenames = dynamic_cast<DBRelControlMySQL*>(global::dbrel()->action)->db_tablenames;
    QStringList newlist;
    for (auto& name : tablenames){
        newlist.append(QString::fromStdString(name));
    }
    return std::move(newlist);
}


/*#include <thread>
#include <chrono>
#include <QRandomGenerator>
using namespace std::chrono_literals;
Result<> Model::tryConnection(std::string address, int port){
    std::this_thread::sleep_for(5000ms);
    if (QRandomGenerator::global()->bounded(2) == 0){
        return value();
    } else {
        return error("Hahahaha, SONIC, YOU LATE");
    }
}*/
