//V 3.0.0

#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <memory>

namespace wholesalegroup {

enum Membership {
    basic,
    preferred
};

struct MemberInfo {
    int id;
    std::string name;
    Membership type;
    std::string expDate; //MM/DD/YYYY
};

struct Purchase {
    std::string item;
    int quantity;
    double price;
    double total;
};

class Member {
public:
    Member(int id, const std::string &name = "NO_PROVIDED_NAME", Membership type = basic, std::string joinDate = "01/01/2000");
    Member(MemberInfo info);

    inline MemberInfo& GetInfo() { return this->info;}
    inline int GetId() const { return this->info.id;}
    inline std::string GetName() const { return this->info.name;}
    inline Membership GetType() const { return this->info.type;}
    inline std::string GetExpDate() const { return this->info.expDate;}
    inline int PurchaseLen() const { return this->size;}
    Purchase& GetPurchase(const std::string &item) const;
    double getAnnualTotal() const;
    double getRebateAmount();
    double getDues() const;

    Purchase& operator[](const std::string &item) const; //can retrieve purchase by passing in item's name
    Purchase& operator[](int index) const; //can retrieve purchase by order purchased

    void AddPurchase(const Purchase &purchase); //if item already exists, add to quantity and update total
    void AddPurchase(const std::string &item, double price, int quantity = 1);

    void UpdatePurchase(const std::string &item, const Purchase &purchase);
    void UpdatePurchase(const std::string &item, double new_price, int new_quantity = 1);
    void SetQuantity(const std::string &item, int new_quantity);
    void SetPrice(const std::string item, int new_price);
    void ChangeItemName(const std::string &old_item_name, const std::string &new_item_name);
    inline void UpdateInfo(Membership new_type, const std::string &new_name) {
        this->info.type = new_type;
        this->info.name = new_name;
    }
    inline void SetType(Membership new_type) { this->info.type = new_type;}
    inline void ChangeName(const std::string &new_name) { this->info.name = new_name;}
    inline void setExpDate(const std::string &expDate) {this->info.expDate = expDate;} //expDate: MM/DD/YYYY

    ~Member();
private:
    MemberInfo info;
    Purchase *purchases;
    int size;
    int allocated;

    void calcExpDate(const std::string &joinDate);
};

} //namespace wholesalegroup

#endif // MEMBER_H
