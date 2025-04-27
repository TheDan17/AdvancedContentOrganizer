#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "../../ui_mainwindow.h"

class View;
class MainWindow : public QMainWindow {
    Q_OBJECT
private:
    Ui::MainWindow *ui;
    View* view;
private slots:
    void on_action_21_triggered();
    void on_action_9_triggered();

    void on_action_17_triggered();

    void on_serverAddButton_clicked();

    void on_action_10_triggered();

    void on_serversAddButton_clicked();

    void on_serversRefresh_clicked();

    void on_addButton_clicked();

    void on_action_5_triggered();

    void on_action_7_triggered();

    void on_action_11_triggered();

public:
    MainWindow(View* view, QWidget *parent = nullptr);
    ~MainWindow();
public slots:
    void tryConnectServer();
signals:
    void addServerTriggered();
};

#endif // MAINWINDOW_H
