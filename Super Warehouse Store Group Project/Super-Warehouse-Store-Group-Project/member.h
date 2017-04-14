//V FINAL

#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <memory>

namespace wholesalegroup {

enum Membership {
    basic,                                                                  //basic - basic type of membership
    preferred                                                               //preferred - preferred type of membership
};

struct MemberInfo {
    int id;                                                                 //id - id of a member
    std::string name;                                                       //name - name of a member
    Membership type;                                                        //type - type of membership
    std::string expDate;                                                    //expDate - expiration date in MM/DD/YYYY
};

struct Purchase {
    std::string item;                                                       //stored item name
    int quantity;                                                           //quantity of stored item
    double price;                                                           //price of item
    double total;                                                           //total cost of purchase
    std::string date;                                                       //date purchased in MM/DD/YYYY
};

class Member {
public:
    Member(int id, const std::string &name = "NO_PROVIDED_NAME",
           Membership type = basic, std::string joinDate = "01/01/2000");   //full constructor
    Member(MemberInfo info);                                                //initialized constructor
    Member(Member& other);                                                  //copy constructor

    inline MemberInfo& GetInfo() { return this->info;}                      //GetInfo - returns member info
    inline int GetId() const { return this->info.id;}                       //GetId - returns id of member
    inline std::string GetName() const { return this->info.name;}           //GetName - returns name of member
    inline Membership GetType() const { return this->info.type;}            //GetType - returns membership type
    inline std::string GetExpDate() const { return this->info.expDate;}     //GetExpDate - returns expiration date
    inline int PurchaseLen() const { return this->size;}                    //PurchaseLen - returns size of purchase
    Purchase& GetPurchase(const std::string &item) const;                   //GetPurchase - returns purchase struct
    double getAnnualTotal() const;                                          //getAnnualTotal - returns annual total
    double getRebateAmount();                                               //getRebateAmount - returns rebate earned
    double getDues() const;                                                 //getDues - returns amount due for membership
    std::string getPurchaseDate(std::string& item) const;                   //getPurchaseDate - returns date of purchase of item

    Purchase& operator[](const std::string &item) const;                    //can retrieve purchase by passing in item's name
    Purchase& operator[](int index) const;                                  //can retrieve purchase by order purchased
    void operator=(Member& other);                                          //assignment operator for member

    void AddPurchase(const Purchase &purchase);                             //AddPurchase - adds purchase struct to member
    void AddPurchase(const std::string &item, double price,
                     std::string date, int quantity = 1);                   //AddPurchase - adds purchase struct to member

    void UpdatePurchase(const std::string &item, const Purchase &purchase); //UpdatePurchase - updates purchase info
    void UpdatePurchase(const std::string &item, double new_price,
                        std::string date, int new_quantity = 1);            //UpdatePurchase - updates purchase info
    void SetQuantity(const std::string &item, int new_quantity);            //SetQuantity - sets the quantity of an item
    void SetPrice(const std::string item, int new_price);                   //SetPrice - sets the price of an item
    void ChangeItemName(const std::string &old_item_name,
                        const std::string &new_item_name);                  //ChangeItemName - changes name of an item
    inline void UpdateInfo(Membership new_type,
                           const std::string &new_name) {                   //UpdateInfo - changes type and name of member
        this->info.type = new_type;
        this->info.name = new_name;
    }
    inline void SetType(Membership new_type) { this->info.type = new_type;}             //SetType - changes the type of a member
    inline void ChangeName(const std::string &new_name) { this->info.name = new_name;}  //ChangeName - changes name of a member
    inline void setExpDate(const std::string &expDate) {this->info.expDate = expDate;}  //setExpDate - expDate: MM/DD/YYYY
    void setPurchaseDate(const std::string &item, const std::string &date);             //setPurchaseDate - changes the date of purchase

    ~Member();
private:
    MemberInfo info;                                                        //info - holds a member's info
    Purchase *purchases;                                                    //purchases - holds all purchases made by member
    int size;                                                               //size - size of purchases
    int allocated;                                                          //allocated - amount used in purchases

    void calcExpDate(const std::string &joinDate);                          //calcExpDate - calcs and sets the expiration date
};

} //namespace wholesalegroup

#endif // MEMBER_H
