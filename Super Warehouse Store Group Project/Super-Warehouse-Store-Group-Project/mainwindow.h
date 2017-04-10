//VERSION 4.1.5
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
        void btn_item_quantity_handler(); // Kit 4/10/2017

        ///***ADDED GROUP FUNCTIONS FROM DAMON'S VERSION
        void btn_checkUpgrade_handler();
        void btn_checkDowngrade_handler();
        void btn_printExpirations_handler();
private slots:
        void on_radioRebate_clicked(bool checked);
        void on_radioButton_clicked(bool checked);
};

#endif // MAINWINDOW_H
