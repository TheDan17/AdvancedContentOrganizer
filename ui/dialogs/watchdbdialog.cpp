#include "watchdbdialog.h"

WatchDBDialog::WatchDBDialog(QWidget* parent, View* view, QStringList tables) :
    QDialog(parent), view(view){
    this->resize(800, 600);
    this->setWindowTitle("Просмотр таблиц БД");
    dialoglayout = new QVBoxLayout(this);

    selector = new QComboBox(this);
    selector->addItems(tables);
    selector->setCurrentIndex(-1);
    selector->setPlaceholderText("Выберите таблицу для отображения");
    dialoglayout->addWidget(selector);

    tablemodel = new QSqlTableModel(this);
    tableview = new QTableView(this);
    tableview->setModel(tablemodel);
    tableview->resizeColumnsToContents();
    tableview->setEditTriggers(QAbstractItemView::NoEditTriggers);

    dialoglayout->addWidget(tableview);

    this->setLayout(dialoglayout);
    connect(selector, &QComboBox::currentTextChanged, this, &WatchDBDialog::newTableSelected);
}
WatchDBDialog::~WatchDBDialog(){}

void WatchDBDialog::newTableSelected(const QString &table){
    tablemodel->setTable(table);
    tablemodel->select();
}
