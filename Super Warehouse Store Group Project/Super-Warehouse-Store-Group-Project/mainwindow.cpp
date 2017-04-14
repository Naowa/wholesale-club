//V FINAL

#include "mainwindow.h"
#include "ui_mainwindow.h"

/**********************************************************
 *
 * MainWindow - O(1)
 *_________________________________________________________
 * constructor
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * parent: QWidget object to run from
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    state = "NONE";
}

/**********************************************************
 *
 * ~MainWindow - O(1)
 *_________________________________________________________
 * destructor
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * dynamic memory of MainWindow is freed
 **********************************************************/
MainWindow::~MainWindow()
{
    delete ui;
}

/**********************************************************
 *
 * get_Str_Input - O(1)
 *_________________________________________________________
 * returns the input in the text box
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * returns string value in text box
 **********************************************************/
string MainWindow::get_Str_Input()
{
    return ui->inputBox->text().toStdString();
}

/**********************************************************
 *
 * display - O(1)
 *_________________________________________________________
 * displays the text of the parameter
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * input_str: string to be displayed
 *
 * POST-CONDITIONS
 * displays the text in the display box
 **********************************************************/
void MainWindow::display(string input_str)
{
    ui->displayBox->setText(QString::fromStdString(input_str));
}

/**********************************************************
 *
 * btn_confirm_handler - O(n^3)
 *_________________________________________________________
 * confirms the input in the text box for the selected
 * button action which sets the state
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * processes the input and chooses the appropriate function
 * call depending on the state set by the clicked button
 **********************************************************/
void MainWindow::btn_confirm_handler()
{
    string input_str = get_Str_Input();
    bool valid = true;
    string input_Type;
    int target_index;

        //Add Member Button
        if (state == "ADD_MEMBER"){
            //if not valid, member not added and error displayed
            superWarehouseGroup.add_member_state(input_str, valid);
                if (valid){
                    ui->instructions->setText("Member Added!");
                    state = "NONE";
                }else{
                    ui->instructions->setText("Invalid Input! ID/NAME/(b/p):");
                }
        }
        //Remove Member Button
        if (state == "REMOVE_MEMBER"){
            superWarehouseGroup.remove_member_state(input_str, valid);
                if (valid){
                    ui->instructions->setText("Member Removed!");
                    state = "NONE";
                }else{
                    ui->instructions->setText("Invalid Input! ID:");
                }
        }
        //Check Upgrade Button
        if (state == "CHECK_UPGRADE"){
            bool upgrade = superWarehouseGroup.checkUpgrade_state(input_str, valid);
                if (valid){
                    if (upgrade){
                        ui->instructions->setText("Upgrade Recommended");
                        state = "NONE";
                    }else{
                        ui->instructions->setText("Upgrade Not Recommended");
                        state = "NONE";
                    }
                }else{
                    ui->instructions->setText("Invalid Input! ID:");
                }
        }
        //View Daily Sales Report Button
        if (state == "DAILY_SALES_REPORT"){
            display(superWarehouseGroup.dailySalesReport(input_str, valid));
            if (!valid)
                ui->instructions->setText("Invalid Input!: FileName:");
        }
        //Check Downgrade Button
        if (state == "CHECK_DOWNGRADE"){
            bool downgrade = superWarehouseGroup.checkDowngrade_state(input_str, valid);
                if (valid){
                    if (downgrade){
                        ui->instructions->setText("Downgrade Recommended");
                        state = "NONE";
                    }else{
                        ui->instructions->setText("Downgrade Not Recommended");
                        state = "NONE";
                    }
                }else{
                    ui->instructions->setText("Invalid Input! ID:");
                }
        }
        //Initialize Day Button
        if (state == "INITIALIZE_DAY"){
            superWarehouseGroup.initialize_day(input_str, valid);
            if(!valid)
                ui->instructions->setText("Invalid Input! Day #:");
        }
        //View Expirations Button
        if (state == "CHECK_EXPIRATIONS"){
            display(superWarehouseGroup.printExpirations(input_str, valid));
            if(!valid)
                ui->instructions->setText("Invalid Input! Month Name:");
        }
        //View All Purchases Button
        if (state == "PURCHASE_HISTORY"){
            superWarehouseGroup.purchase_history_state(input_str, valid, target_index, input_Type);

                //reading input as id
                if (input_Type == "ID"){
                    if (valid){
                        if (target_index == -1){
                            valid = false;
                            ui->instructions->setText("Not Found! ID or NAME:");
                        }

                        if (valid){
                            display(superWarehouseGroup.get_Member_Purchases_String(target_index));
                            ui->instructions->setText("Purchased History Displayed!");
                            state = "NONE";
                        }
                    }else{
                        ui->instructions->setText("Invalid Input! ID or NAME:");
                    }

                //reading input as name
                }else{
                    if (valid){
                        //if not found
                        if (target_index == -1){
                            valid = false;
                            ui->instructions->setText("Not Found! ID or NAME:");
                        }

                        //if more than 1 found
                        if (target_index == -2){
                            valid = false;
                            ui->instructions->setText("Duplicates Found: ID:");
                            state = "PURCHASE_HISTORY_SPECIAL";
                        }

                        if (valid){
                            display(superWarehouseGroup.get_Member_Purchases_String(target_index));
                            ui->instructions->setText("Purchased History Displayed!");
                            state = "NONE";
                        }
                    }else{
                        ui->instructions->setText("Invalid Input! ID or NAME:");
                    }
                }
        }

        if (valid){
            if (state == "PURCHASE_HISTORY_SPECIAL"){
                superWarehouseGroup.purchase_history_special_state(input_str, valid, target_index);
                    if (valid){
                        if (target_index == -1){
                            valid = false;
                            state = "PURCHASE_HISTORY";
                            ui->instructions->setText("Not Found! ID or NAME:");
                        }

                        if (valid){
                            display(superWarehouseGroup.get_Member_Purchases_String(target_index));
                            ui->instructions->setText("Purchased History Displayed!");
                            state = "NONE";
                        }
                    }else{
                        state = "PURCHASE_HISTORY";
                        ui->instructions->setText("Invalid Input! ID or NAME:");
                    }
            }
        }
        //Item Quantities Button
        if (state == "ITEM_QUANTITY")
        {
            string itemInfo;
            int quantity = 0;
            double price = 0;
            superWarehouseGroup.printItemInfo(input_str, quantity, price, valid);
            if(valid)
            {
                ui->instructions->setText("Item Found.");
                itemInfo = input_str + " \nQuantity: ";
                itemInfo += std::to_string(quantity);
                itemInfo += " \nPrice: ";
                itemInfo += std::to_string(price);
                itemInfo += "\n";
                display(itemInfo);
                state = "NONE";
            }
            else
            {
                ui->instructions->setText("Invalid Item Name!");
            }
        }
}

/**********************************************************
 *
 * btn_add_handler - O(1)
 *_________________________________________________________
 * prepares UI to add member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI text changed to add member
 **********************************************************/
void MainWindow::btn_add_handler()
{
    ui->instructions->setText("Add: ID/NAME/(b/p):");
    state = "ADD_MEMBER";
}

/**********************************************************
 *
 * btn_remove_handler - O(1)
 *_________________________________________________________
 * prepares UI to remove member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI text changed to remove member
 **********************************************************/
void MainWindow::btn_remove_handler()
{
    ui->instructions->setText("Remove: ID:");
    state = "REMOVE_MEMBER";
}

/**********************************************************
 *
 * btn_purchases_handler - O(1)
 *_________________________________________________________
 * prepares UI to view purchase history
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to view purchases
 **********************************************************/
void MainWindow::btn_purchases_handler()
{
    ui->instructions->setText("Purchase History: ID or NAME:");
    state = "PURCHASE_HISTORY";

}

/**********************************************************
 *
 * btn_display_handler - O(1)
 *_________________________________________________________
 * prepares UI to display member info
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to display member info
 **********************************************************/
void MainWindow::btn_display_handler()
{
    ui->instructions->setText("Members Displayed!");
    superWarehouseGroup.get_Members_String();
    display(superWarehouseGroup.get_Members_String());
}

/**********************************************************
 *
 * btn_iem_quantity_handler - O(1)
 *_________________________________________________________
 * prepares UI view quantity
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to view an item's quantity info
 **********************************************************/
void MainWindow::btn_item_quantity_handler()
{
    ui->instructions->setText("Item Name:");
    state = "ITEM_QUANTITY";
}

/**********************************************************
 *
 * btn_viewAllPurchases_handler - O(1)
 *_________________________________________________________
 * prepares UI to viw all purchases
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to view all purchases
 **********************************************************/
void MainWindow::btn_viewAllPurchases_handler()
{
    ui->instructions->setText("Purchases Displayed!");
    display(superWarehouseGroup.get_All_Purchases_String());
}

/**********************************************************
 *
 * btn_QtySold_handler - O(1)
 *_________________________________________________________
 * prepares UI to view quantity of an item
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to view quantity of an item sold
 **********************************************************/
void MainWindow::btn_QtySold_handler()
{
    ui->instructions->setText("Quantities Sold Displayed!");
    display(superWarehouseGroup.get_Quantities_Sold_String());
}

/**********************************************************
 *
 * btn_checkUpgrade_handler - O(1)
 *_________________________________________________________
 * prepares UI to check a member for upgrade potential
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to check if its beneficial to upgrade membership
 **********************************************************/
void MainWindow::btn_checkUpgrade_handler()
{
    ui->instructions->setText("Check Upgrade: ID:");
    state = "CHECK_UPGRADE";
}

/**********************************************************
 *
 * btn_checkDowngrade_handler - O(1)
 *_________________________________________________________
 * prepares UI to check a member for downgrade potential
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to check if its beneficial to downgrade membership
 **********************************************************/
void MainWindow::btn_checkDowngrade_handler()
{
    ui->instructions->setText("Check Downgrade: ID:");
    state = "CHECK_DOWNGRADE";
}

/**********************************************************
 *
 * btn_printExpirations_handler - O(1)
 *_________________________________________________________
 * prepares UI to view membership expirations
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to view all membership expirations in a given
 * month
 **********************************************************/
void MainWindow::btn_printExpirations_handler()
{
    ui->instructions->setText("Check Expirations: Month Name:");
    state = "CHECK_EXPIRATIONS";
}

/**********************************************************
 *
 * btn_initialize_day_handler - O(1)
 *_________________________________________________________
 * initializes the day txt files
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * initializes all the info from the txt files to the
 * program's data
 **********************************************************/
void MainWindow::btn_initialize_day_handler()
{
    ui->instructions->setText("Initialize day: Day #:");
    state = "INITIALIZE_DAY";
}

/**********************************************************
 *
 * btn_daily_sales_report - O(1)
 *_________________________________________________________
 * prepares UI to display a daily sales report
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to display a daily sales report showing
 * all the info for a given day
 **********************************************************/
void MainWindow::btn_daily_sales_report()
{
    ui->instructions->setText("View Sales Report: FileName:");
    state = "DAILY_SALES_REPORT";
}

/**********************************************************
 *
 * btn_rebate_handler - O(1)
 *_________________________________________________________
 * prepares UI to view rebate
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to check the rebate amount for a member
 **********************************************************/
void MainWindow::btn_rebate_handler()
{
  string toPrint = superWarehouseGroup.printRebates();
  display(toPrint);
}

/**********************************************************
 *
 * btn_dues_handler - O(1)
 *_________________________________________________________
 * prepares UI to view membership dues
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * UI changed to check the membership dues owed for a member
 **********************************************************/
void MainWindow::btn_dues_handler()
{
    string toPrint = superWarehouseGroup.printMembershipDues();
    display(toPrint);
}
