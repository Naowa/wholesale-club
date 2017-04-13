//V 3.1.1

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
    typedef Member value_type;
    typedef Member* memPtr;
    typedef std::size_t size_type;

    group();
    void printFullSalesReport();
    void printMemberPurchases(string memName);
    void printMemberPurchases(int memId);
    void printAllPurchases();
    void printItemInfo(string &itemName, int &quantity, double &price, bool &valid);
    void printItemQuantities();
    string printRebates();
    string printMembershipDues();
    string printExpirations(string month, bool &valid);
    void addMember(value_type m);
    void removeMember(value_type m);
    void initialize_day(string fileName, bool &valid);
    bool checkUpgrade_state(string input_str, bool &valid);
    bool checkDowngrade_state(string input_str, bool &valid);
    void add_member_state(string input_str, bool &valid);
    void remove_member_state(string input_str, bool &valid);
    void purchase_history_state(string input_str, bool &valid, int &target_index, string &input_Type);
    void purchase_history_special_state(string input_str, bool &valid, int &target_index);
    string get_Member_Purchases_String(int index);
    string get_Members_String();
    string get_All_Purchases_String();
    string get_Quantities_Sold_String();
    // Need to Add
    string dailySalesReport(string dayDate, bool &valid);
private:
    Sequence memberList;
    void initialize_members();
    int inventory_cap;
    int inventory_sz;
    string *ItemNames;
    void sort_inventory();
    void expand_inventory();
    bool inventory_contains(string input);
    void add_item(string input);
    void initialize_inventory();

};

#endif // GROUP_H
