#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    state = "NONE";
    warehouse_members.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}


//every button will use this function to confirm input
//state conditional determines what is being confirmed
//based on what button was clicked, state is updated
void MainWindow::btn_confirm_handler()
{
    QString qstr;
    //input str is read from box
    string input_str = ui->inputBox->text().toStdString();

    //does not include error checking, how should it be implemented?
    if (state == "ADD_MEMBER"){
        int id;
        string id_str;
        string name;
        int i = 0;

            //id and names read in format: id/name
            //store id
            while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
                id_str += input_str[i];
                i++;
            }
        id = stoi(id_str);

        i++;
            //store name
            while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
                name += input_str[i];
                i++;
            }
        wholesalegroup::Member new_member(id, name);
        wholesalegroup::Member *member_ptr = &new_member;
//        warehouse_members.add_member(new_member);

        warehouse_members.insert(member_ptr);
        warehouse_members.advance();

//        qstr = QString::fromStdString(to_string(warehouse_members[0].GetId()));

        ///////////////////////////////////////////**************************
        /// this should bein the btn handler******************************

        qstr += QString::fromStdString(to_string(warehouse_members.Get_Used()));

        ui->test->setText(qstr);

        /////////////////////////////////////////////**************************
    }
    if (state == "REMOVE_MEMBER"){
        int id;
        string id_str;
        string name;
        int i = 0;

            //id and names read in format: id/name
            //store id
            while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
                id_str += input_str[i];
                i++;
            }
        id = stoi(id_str);

        i++;
            //store name
            while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
                name += input_str[i];
                i++;
            }

//        warehouse_members.remove_member(id, name);
    }


        //test output stuff
//        qstr = QString::fromStdString(name);
//        ui->test->setText(qstr);



    //final step, call sequence add function
//    sequence.add_member(id, name);
}

///**************************************sequence class
//void expand()
//{
//    //value_type is going to be member
//    //double the capacity, make new arr ptr
//    cap *= 2;
//    value_type *new_data;

//    //set new arr to siz cap
//    new_data = new value_type[cap];
//    copy(data, data + used, new_data);
//    delete [] data;
//    data = new_data;
//}

//void Add_Member(Member &addend)
//{
//        if ( (size + 1) > cap){
//            expand();
//        }
//    data[used] = addend;
//    used++;
//}

//void Remove_Member(int target_id, string target_name){
//    for (int i = 0; i < used; i++){
//        if ( (data[i].id == target_id) && (data[i].name == target_name) ){
//            for (int j = i; j < (used - 1); j++){
//                data[i] = data[i + 1];
//            }
//            used--;
//        }
//    }
//}
///***************************************

void MainWindow::btn_add_handler()      //add a member type basic or pref
{
    ui->instructions->setText("Add: ID/NAME");
    state = "ADD_MEMBER";
}

void MainWindow::btn_remove_handler()
{
    ui->instructions->setText("Remove: ID/Name");
    state = "REMOVE_MEMBER";
}

//used is updating, but array not adding members?
//use new?
void MainWindow::btn_print_handler()
{
    QString qstr;


//    string id_str;
//    int temp = members[0]->GetId();
//    id_str = to_string(temp);
//    qstr = QString::fromStdString(id_str);
//    ui->test->setText(qstr);

//    qstr += QString::fromStdString(to_string(warehouse_members.Get_Used()));

//    ui->test->setText(qstr);

//    qstr = QString::fromStdString(to_string(warehouse_members[0].GetId()));

    ui->test->setText(qstr);
}
