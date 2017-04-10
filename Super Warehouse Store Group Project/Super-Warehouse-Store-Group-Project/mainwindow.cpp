//VERSION 4.1.5

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    state = "NONE";
}

MainWindow::~MainWindow()
{
    delete ui;
}

string MainWindow::get_Str_Input()
{
    return ui->inputBox->text().toStdString();
}

void MainWindow::display(string input_str)
{
    ui->displayBox->setText(QString::fromStdString(input_str));
}


//every button will use this function to confirm input
//state conditional determines what is being confirmed
//based on what button was clicked, state is updated
void MainWindow::btn_confirm_handler()
{
    string input_str = get_Str_Input();
    bool valid = true;
    string input_Type;
    int target_index;

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

        if (state == "REMOVE_MEMBER"){
            superWarehouseGroup.remove_member_state(input_str, valid);
                if (valid){
                    ui->instructions->setText("Member Removed!");
                    state = "NONE";
                }else{
                    ui->instructions->setText("Invalid Input! ID:");
                }
        }

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

        if (state == "CHECK_EXPIRATIONS"){
            display(superWarehouseGroup.printExpirations(input_str, valid));
            if(!valid)
                ui->instructions->setText("Invalid Input! Month Name:");
        }

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

void MainWindow::btn_add_handler()
{
    ui->instructions->setText("Add: ID/NAME/(b/p):");
    state = "ADD_MEMBER";
}

void MainWindow::btn_remove_handler()
{
    ui->instructions->setText("Remove: ID:");
    state = "REMOVE_MEMBER";
}

void MainWindow::btn_purchases_handler()
{
    ui->instructions->setText("Purchase History: ID or NAME:");
    state = "PURCHASE_HISTORY";

}

void MainWindow::btn_display_handler()
{
    ui->instructions->setText("Members Displayed!");
    superWarehouseGroup.get_Members_String();
    display(superWarehouseGroup.get_Members_String());
}

void MainWindow::btn_item_quantity_handler()                // Kit 4/10/2017
{
    ui->instructions->setText("Item Name:");
    state = "ITEM_QUANTITY";
}




///***ADDED GROUP FUNCTIONS FROM DAMON'S VERSION
void MainWindow::btn_checkUpgrade_handler()
{
    ui->instructions->setText("Check Upgrade: ID:");
    state = "CHECK_UPGRADE";
}

void MainWindow::btn_checkDowngrade_handler()
{
    ui->instructions->setText("Check Downgrade: ID:");
    state = "CHECK_DOWNGRADE";
}

void MainWindow::btn_printExpirations_handler()
{
    ui->instructions->setText("Check Expirations: Month Name:");
    state = "CHECK_EXPIRATIONS";
}



/// ***KIT'S Functions
void MainWindow::on_radioRebate_clicked(bool checked)
{
  string toPrint = superWarehouseGroup.printRebates();
  display(toPrint);
  // ui->displayBox->setText(toPrint);
}

void MainWindow::on_radioButton_clicked(bool checked)
{
    string toPrint = superWarehouseGroup.printMembershipDues();
    display(toPrint);
}
