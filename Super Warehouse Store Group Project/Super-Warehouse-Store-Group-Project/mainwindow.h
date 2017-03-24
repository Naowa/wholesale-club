#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <iostream>
#include "sequence.h"
#include "member.h"
#include <string>

using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        string state;
        Sequence warehouse_members;

    public slots:
        void btn_confirm_handler();
        void btn_add_handler();
        void btn_remove_handler();
        void btn_print_handler();
};

#endif // MAINWINDOW_H
