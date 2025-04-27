#include "additemtoserverdialog.h"

AddItemToServerDialog::AddItemToServerDialog(std::string server, std::vector<std::pair<int, std::string>> items, QWidget *parent)
    : QDialog(parent), ui(new Ui::AddItemToServerDialog), items(items) {
    ui->setupUi(this);

    ui->serverSelectComboBox->addItem(server.c_str());
    for (auto& pair : items){
        ui->itemParentComboBox->addItem(pair.second.c_str());
    }

    typeGroup = new QButtonGroup(this);
    typeGroup->addButton(ui->dirItemRButton);
    typeGroup->addButton(ui->fileItemRButton);
    storeGroup = new QButtonGroup(this);
    storeGroup->addButton(ui->diskItemRButton);
    storeGroup->addButton(ui->cloudItemRButton);

    connect(this->ui->nextButton, &QPushButton::clicked, this, &QDialog::accept);
    connect(this->ui->cloudItemRButton, &QRadioButton::toggled, [this](bool checked){ ui->storagePathItemEdit->setDisabled(false); });
    connect(this->ui->diskItemRButton, &QRadioButton::toggled, [this](bool checked){ ui->storagePathItemEdit->setDisabled(false); });

    connect(ui->cloudItemRButton, &QRadioButton::clicked, this, &AddItemToServerDialog::on_RButton_clicked);
    connect(ui->diskItemRButton, &QRadioButton::clicked, this, &AddItemToServerDialog::on_RButton_clicked);
    connect(ui->dirItemRButton, &QRadioButton::clicked, this, &AddItemToServerDialog::on_RButton_clicked);
    connect(ui->fileItemRButton, &QRadioButton::clicked, this, &AddItemToServerDialog::on_RButton_clicked);
    connect(ui->itemParentComboBox, &QComboBox::currentIndexChanged, this, &AddItemToServerDialog::on_ComboBox_choosed);
    connect(ui->serverSelectComboBox, &QComboBox::currentIndexChanged, this, &AddItemToServerDialog::on_ComboBox_choosed);
    connect(ui->storagePathItemEdit, &QLineEdit::textChanged, this, &AddItemToServerDialog::on_LineEdit_edited);
}

AddItemToServerDialog::~AddItemToServerDialog() {
    delete typeGroup;
    delete storeGroup;
    delete ui;
}

#include <QMessageBox>
void AddItemToServerDialog::on_helpButton_clicked() {
    QString msg = "Здесь вы можете добавить предмет на сервер, на котором вы имеете права для этого.\n";
    msg += "Соответственно, владельцы серверов имеют такое право по умолчанию.\n";
    msg += "Если выбираете пункт 'Облако', то в поле пути поместите ссылку доступа на уже загруженный файл.\n";
    msg += "Если же выбранный пункт - 'Диск', то это должен быть путь на файл на вашем компьютере.\n";
    msg += "Если же выбранный пункт - 'Раздел', то это будет его имя.";
    QMessageBox::information(this, "Небольшая справка", msg);
}

void AddItemToServerDialog::fetchData(){
    addServer = ui->serverSelectComboBox->currentText();
    QString item_str = ui->itemParentComboBox->currentText();
    int item_id = -1;
    for (auto& pair : items){
        if (item_str == pair.second.c_str()){
            item_id = pair.first;
            break;
        }
    }
    addParent = item_id;

    if (ui->fileItemRButton->isChecked()) {
        if (ui->cloudItemRButton->isChecked()) { addStorage = cloud; }
        else if (ui->diskItemRButton->isChecked()) { addStorage = disk; }
        else { addStorage = noneStorage; }
    } else { addStorage = noneStorage; }

    if (ui->fileItemRButton->isChecked())
        addType = file;
    else if (ui->dirItemRButton->isChecked())
        addType = dir;
    else
        addType = noneType;

    addPath = ui->storagePathItemEdit->text();
}

addItemData AddItemToServerDialog::getData() {
    fetchData();
    return {addServer, addParent, addType, addStorage, addPath};
}

void AddItemToServerDialog::controlDisabling() {
    ui->nextButton->setDisabled(true);
    if (ui->dirItemRButton->isChecked()){
        ui->diskItemRButton->setDisabled(true);
        ui->cloudItemRButton->setDisabled(true);
        ui->storagePathItemEdit->setDisabled(false);
    } else {
        ui->diskItemRButton->setDisabled(false);
        ui->cloudItemRButton->setDisabled(false);
        if (!ui->diskItemRButton->isChecked() && !ui->cloudItemRButton->isChecked())
            ui->storagePathItemEdit->setDisabled(true);
    }

    fetchData();
    if (addType != noneType && !addServer.isEmpty() && !addPath.isEmpty()){
        ui->nextButton->setDisabled(false);
    } else if (addType == file && addStorage == noneStorage) {
        ui->nextButton->setDisabled(true);
    }
}

void AddItemToServerDialog::on_RButton_clicked(){ controlDisabling(); }
void AddItemToServerDialog::on_LineEdit_edited(QString text){ controlDisabling(); }
void AddItemToServerDialog::on_ComboBox_choosed(int index){ controlDisabling(); }
