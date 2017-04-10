//v1.4.11
//UPDATE NOTES:
//Interfaced functions indicated below with the GUI

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
    void printFullSalesReport();                                //1 on assignment list
    void printMemberPurchases(string memName);  //2
    void printMemberPurchases(int memId);            //2
    void printAllPurchases();                                    //3
    void printItemInfo(string &itemName, int &quantity, double &price, bool &valid);                 //4
    void printItemQuantities();                                //5
    string printRebates();                                        //6
    string printMembershipDues();                           //7
    string printExpirations(string month, bool &valid);                   //8
    void addMember(value_type m);                       //9
    void removeMember(value_type m);                  //9

    ///***CHECK UP AND DOWN IMPLEMENTED
    bool checkUpgrade_state(string input_str, bool &valid);            //10
    bool checkDowngrade_state(string input_str, bool &valid);          //11



    ///***ALL NEW FUNCTIONS IN THIS VERSION DEFINED BELOW
    void add_member_state(string input_str, bool &valid);
    void remove_member_state(string input_str, bool &valid);
    void purchase_history_state(string input_str, bool &valid, int &target_index, string &input_Type);
    void purchase_history_special_state(string input_str, bool &valid, int &target_index);
    string get_Member_Purchases_String(int index);
    string get_Members_String();
    ///***END OF NEW FUNCTIONS IN THIS VERSION
    void initialize_members();
private:
    Sequence memberList;
};

#endif // GROUP_H
