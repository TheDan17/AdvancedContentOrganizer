#ifndef WATCHDBDIALOG_H
#define WATCHDBDIALOG_H

#include <QString>
#include <QStringList>
#include <QDialog>
#include <QVBoxLayout>
#include <QComboBox>
#include <QTableView>
#include <QSqlTableModel>

#include "../../main/mvc/view.h"

class WatchDBDialog : public QDialog {
    Q_OBJECT
private:
    View* view;
    QVBoxLayout* dialoglayout;
    QComboBox* selector;
    QTableView* tableview;
    QSqlTableModel* tablemodel;
private slots:
    void newTableSelected(const QString &table);
public:
    explicit WatchDBDialog(QWidget* parent, View* view, QStringList tables);
    ~WatchDBDialog();
};

#endif // WATCHDBDIALOG_H
