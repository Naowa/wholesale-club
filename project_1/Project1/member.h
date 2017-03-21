#ifndef MEMBER_H
#define MEMBER_H

#include <string>
#include <memory>

namespace wholesalegroup {

enum Membership {
    basic,
    premium,
};

struct MemberInfo {
    int id;
    std::string name;
    Membership type;
};

struct Purchase {
    std::string item;
    int quantity;
    double price;
    double total;
};

class Member {
public:
    Member(int id, const std::string &name = "NO_PROVIDED_NAME", Membership type = basic);
    Member(MemberInfo info);

    inline MemberInfo& GetInfo() { return this->info;} //why can't this be const?
    inline int GetId() const { return this->info.id;}
    inline std::string GetName() const { return this->info.name;}
    inline Membership GetType() const { return this->info.type;}
    inline int PurchaseLen() const { return this->size;}
    Purchase& GetPurchase(const std::string &item) const;

    Purchase& operator[](const std::string &item) const; //can retrieve purchase by passing in item's name
    Purchase& operator[](int index) const; //can retrieve purchase by order purchased

    void AddPurchase(const Purchase &purchase); //if item already exists, add to quantity and update total
    void AddPurchase(const std::string &item, double price, int quantity = 1);

    void UpdatePurchase(const std::string &item, const Purchase &purchase);
    void UpdatePurchase(const std::string &item, int new_quantity, double new_price);
    void SetQuantity(const std::string &item, int new_quantity);
    void SetPrice(const std::string item, int new_price);
    void ChangeItemName(const std::string &old_item_name, const std::string &new_item_name);
    inline void UpdateInfo(Membership new_type, const std::string &new_name) {
        this->info.type = new_type;
        this->info.name = new_name;
    }
    inline void SetType(Membership new_type) { this->info.type = new_type;}
    inline void ChangeName(const std::string &new_name) { this->info.name = new_name;}

    ~Member();
private:
    MemberInfo info;
    Purchase *purchases;
    int size;
    int allocated;
};

} //namespace wholesalegroup

#endif // MEMBER_H
