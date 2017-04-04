//VERSION 4.1.1
//UPDATE NOTES:
//Everything here is different from the old version

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "group.h";

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

        //DRIVER CLASS/GROUP MANAGEMENT VARIABLES
        string state;
        group superWarehouseGroup;

        //PRIVATE HELPER FUNCTIONS
        string get_Str_Input();
        void display(string input_str);
    public slots:
        void btn_confirm_handler();
        void btn_add_handler();
        void btn_remove_handler();
        void btn_purchases_handler();
        void btn_display_handler();

        ///***ADDED GROUP FUNCTIONS FROM DAMON'S VERSION
        void btn_checkUpgrade_handler();
        void btn_checkDowngrade_handler();
};

#endif // MAINWINDOW_H
