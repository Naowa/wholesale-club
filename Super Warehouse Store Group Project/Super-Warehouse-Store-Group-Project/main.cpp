/*********************************************************
 * AUTHOR : Andy Tang, Kit Ha, Armen Mouradyan, Damon Nguyen
 * Project: Super Warehouse Store Group Project
 * CLASS : CS008
 * SECTION : MW: 7:00am - 8:25am, F: 7:00am - 11:15am
 * Due Date : 4/14/17
 *********************************************************/

#include <QApplication>
#include <iostream>
#include "mainwindow.h"
#include "member.h"

using namespace wholesalegroup;
using namespace std;

/**********************************************************
 * Super Warehouse Store Group Project
 *_________________________________________________________
 * implement a super warehouse store
 * implement interactive gui
 * implement various functions for managing members
 * implement various reports for member information
 *_________________________________________________________
 * INPUT:
 * buttons: user will press buttons to access different
 * functions of the program
 *
 * input: if prompted, the user will input the requested information
 * into the input box and confirm using the universal "ok" button to
 * confirm their input
 *
 * OUTPUT:
 * GUI: the ui will display information based on what
 * functions are being used
 **********************************************************/

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
