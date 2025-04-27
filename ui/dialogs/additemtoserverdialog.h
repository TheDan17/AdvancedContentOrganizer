#ifndef ADDITEMTOSERVERDIALOG_H
#define ADDITEMTOSERVERDIALOG_H

#include <vector>
#include <string>
#include <QString>
#include <QDialog>
#include <QButtonGroup>

#include "ui_additemtoserverdialog.h"

enum itemType {dir, file, noneType};
enum itemStorage{cloud, disk, noneStorage};

struct addItemData {
    QString addServer;
    int addParent;
    enum itemType addType;
    enum itemStorage addStorage;
    QString addPath;
};

class AddItemToServerDialog : public QDialog {
    Q_OBJECT
private:
    Ui::AddItemToServerDialog *ui;
    QButtonGroup* typeGroup;
    QButtonGroup* storeGroup;
    std::vector<std::pair<int, std::string>> items;

    QString addServer;
    int addParent;
    enum itemType addType;
    enum itemStorage addStorage;
    QString addPath;
public:
    explicit AddItemToServerDialog(std::string server, std::vector<std::pair<int, std::string>> items, QWidget *parent = nullptr);
    ~AddItemToServerDialog();
    void fetchData();
    addItemData getData();
    void controlDisabling();
private slots:
    void on_helpButton_clicked();
    void on_dirItemRButton_clicked(){}
    void on_RButton_clicked();
    void on_LineEdit_edited(QString text);
    void on_ComboBox_choosed(int index);
};

#endif // ADDITEMTOSERVERDIALOG_H
