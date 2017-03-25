//v0.0.3
#ifndef GROUP_H
#define GROUP_H

#include "member.h"
#include "sequence.h"

using namespace wholesalegroup;

class group
{
public:
    typedef Member value_type;
    typedef Member* memPtr;
    typedef std::size_t size_type;

    group();
    void printFullSalesReport();                //1 on assignment list
    void printMemberPurchases(string memName);  //2
    void printMemberPurchases(int memId);       //2
    void printAllPurchases();                   //3
    void printItemInfo(string itemName);        //4
    void printItemQuantities();                 //5
    void printRebates();                        //6
    void printMembershipDues();                 //7
    void printExpirations(string month);        //8
    void addMember(value_type m);               //9
    void removeMember(value_type m);            //9
    bool checkUpgrade(value_type m);            //10
    bool checkDowngrade(value_type m);          //11
private:
    Sequence memberList;
};

#endif // GROUP_H
