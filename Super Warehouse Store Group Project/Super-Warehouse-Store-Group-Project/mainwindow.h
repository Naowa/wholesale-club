//V 1.3.3.7

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
        Ui::MainWindow *ui;                             //ui - GUI object that the user sees
        string state;                                   //state - state that the GUI is in
        group superWarehouseGroup;                      //superWarehouseGroup - initializes the warehouse group's functions
        string get_Str_Input();                         //get_Str_Input - converts user input into a string
        void display(string input_str);                 //display - displays a string to the ui
    public slots:
        void btn_confirm_handler();                     //btn_confirm_handler - universal button that manages the various GUI functions
        void btn_add_handler();                         //btn_add_handler - handles the button for adding members
        void btn_remove_handler();                      //btn_remove_handler - handles button for removing members
        void btn_purchases_handler();                   //btn_purchases_handler - handles purchases button
        void btn_display_handler();                     //btn_display_handler - handles display button
        void btn_item_quantity_handler();               //btn_item_quantity_handler - handles item quantity button
        void btn_viewAllPurchases_handler();            //btn_viewAllPurchases_handler - handles view all purchases button
        void btn_QtySold_handler();                     //btn_QtySold_handler - handles quantity sold button
        void btn_checkUpgrade_handler();                //btn_checkUpgrade_handler - handles upgrade check button
        void btn_checkDowngrade_handler();              //btn_checkDowngrade_handler - handles downgrade check button
        void btn_printExpirations_handler();            //btn_printExpirations_handler - handles print expiration button
        void btn_initialize_day_handler();              //btn_initialize_day_handler - handles
        void btn_daily_sales_report();                  //btn_daily_sales_report - handles daily sales report button
        void btn_rebate_handler();                      //btn_rebate_handler - handles radio button for rebates
        void btn_dues_handler();                        //btn_dues_handler - handles radio button for dues
};

#endif // MAINWINDOW_H
