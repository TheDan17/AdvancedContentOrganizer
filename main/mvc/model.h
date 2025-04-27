#ifndef MODEL_H
#define MODEL_H

#include <QStringList>

#include "../../utils/resulthandler.h"
#include "../../components/network/client.h"
#include "../../components/network/host.h"

#include "../../ui/dialogs/additemtoserverdialog.h" // TODO struct separate dialog

class Model {
public:
    Host* host;
    Client* client;
    Model();
    Result<> init_model();
    Result<> start_host();

    Result<> tryConnection(std::string address, int port);
    Result<> tryAddToDatabase(addItemData itemData);

    std::vector<std::pair<int, std::string>> get_dir_items();
    QStringList getDBTableNames();
};

#endif // MODEL_H
