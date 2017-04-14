//V FINAL

#ifndef GROUP_H
#define GROUP_H

#include "member.h"
#include "sequence.h"

using namespace wholesalegroup;
using std::string;

#include <string>

class group
{
public:
    typedef Member value_type;                                                          //value_type - typedef for a Member value type
    typedef Member* memPtr;                                                             //memPtr - typedef for a pointer to a member
    typedef std::size_t size_type;                                                      //size_type - typedef for size_t

    group();                                                                            //group - default group constructor
    void printItemInfo(string &itemName, int &quantity,
                       double &price, bool &valid);                                     //printItemInfo - calculates total quantity and price of an item
    string printRebates();                                                              //printRebates - determines rebates and returns a string to display
    string printMembershipDues();                                                       //printMembershipDues - determines dues and returns a string to display
    string printExpirations(string month, bool &valid);                                 //printExpirations - determines expiring members of a month and returns a string to display
    void initialize_day(string fileName, bool &valid);                                  //initialize_day - initializes member and purchse info for a particular day input
    bool checkUpgrade_state(string input_str, bool &valid);                             //checkUpgrade_state - checks if a member should upgrade
    bool checkDowngrade_state(string input_str, bool &valid);                           //checkDowngrade_state - checks if a member should downgrade
    void add_member_state(string input_str, bool &valid);                               //add_member_state - adds a member based on input
    void remove_member_state(string input_str, bool &valid);                            //remove_member_state - removes a member based on input
    void purchase_history_state(string input_str,
                                bool &valid, int &target_index, string &input_Type);    //purchase_history_state - determines if user is searching purchase history with id or name
    void purchase_history_special_state(string input_str,
                                        bool &valid, int &target_index);                //purchase_history_special_state - handles when duplicate names are found, works with previous version
    string get_Member_Purchases_String(int index);                                      //get_Member_Purchases_String - returns a string to display a member's purchases
    string get_Members_String();                                                        //get_Members_String - returns a string to display all member info
    string get_All_Purchases_String();                                                  //get_All_Purchases_String - returns a string to display all purchases
    string get_Quantities_Sold_String();                                                //get_Quantities_Sold_String - returns a string to display all quantities of items sold
    string dailySalesReport(string dayDate, bool &valid);                               //dailySalesReport - returns a string with daily sales report to display
private:
    Sequence memberList;                                                                //memberList - sequence of member objects
    void initialize_members();                                                          //initialize_members - initializes members from txt
    int inventory_cap;                                                                  //inventory_cap - capacity of inventory
    int inventory_sz;                                                                   //inventory_sz - sz of inventory
    string *ItemNames;                                                                  //ItemNames - pointer to a string array of item names
    void sort_inventory();                                                              //sort_inventory - sorts inventory alphabetically
    void expand_inventory();                                                            //expand_inventory - doubles the inventory allocated space
    bool inventory_contains(string input);                                              //inventory_contains - checks if inventory contains an item name
    void add_item(string input);                                                        //add_item - adds an item name to the inventory
    void initialize_inventory();                                                        //initialize_inventory - initializes the inventory with current member data
};

#endif // GROUP_H
