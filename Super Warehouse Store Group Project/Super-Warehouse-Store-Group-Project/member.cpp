//V 1.3.3.7

#include <cassert>
#include <cstdlib>
#include "member.h"

using std::string;
using std::stoi;
using std::to_string;
using std::copy;

//O(n^2)
wholesalegroup::Member::Member(int id, const std::string &name, Membership type, string joinDate) {
    this->info.id = id;
    this->info.name = name;
    this->info.type = type;
    this->size = 0;
    this->allocated = 10;

    purchases = new Purchase[this->allocated];

    calcExpDate(joinDate);
}

//O(1)
wholesalegroup::Member::Member(MemberInfo info) {
    this->info = info;
    purchases = new Purchase[this->allocated];
}

//O(n)
wholesalegroup::Member::Member(Member& other) {
    this->operator=(other);
}

//O(n)
void wholesalegroup::Member::operator=(Member& other) {
    this->info = other.info;
    this->allocated = other.allocated;
    this->size = other.size;
    this->purchases = new Purchase[this->allocated];
    copy(other.purchases, other.purchases + allocated, this->purchases);
}

//O(n)
wholesalegroup::Purchase& wholesalegroup::Member::GetPurchase(const string &item) const {
    for (int i = 0; i < this->size; i++) {
        if (this->purchases[i].item == item) {
            return this->purchases[i];
        }
    }

    return this->purchases[0]; //this would count as an error
}

//O(n)
double wholesalegroup::Member::getAnnualTotal() const {
    double total;

    total = 0;

    for (int i = 0; i < this->size; i++ ) {
        total += this->purchases[i].price;
    }

    return total;
}

//O(1)
double wholesalegroup::Member::getRebateAmount() {
    if (this->info.type == basic) {
        return 0;
    }

    return this->getAnnualTotal() * 0.05;
}

//O(1)
double wholesalegroup::Member::getDues() const {
    double BASIC_DUES = 60;
    double PREF_DUES = 75;

    if (this->info.type == basic) {
        return BASIC_DUES;
    }

    return PREF_DUES;
}

//O(1)
string wholesalegroup::Member::getPurchaseDate(string& item) const{
    return this->operator[](item).date;
}

//O(1)
wholesalegroup::Purchase& wholesalegroup::Member::operator[](const string &item) const {
    return this->GetPurchase(item);
}

//O(1)
wholesalegroup::Purchase& wholesalegroup::Member::operator[](int index) const {
    assert(index < this->PurchaseLen());

    return this->purchases[index];
}

//O(n)
void wholesalegroup::Member::AddPurchase(const Purchase &new_purchase) {
    bool exist = false;

    for (int i = 0; i < this->size; i++) {
        if (this->purchases[i].item == new_purchase.item) {
            exist = true;
        }
    }

    if (!exist) {
        if (this->size + 1 > this->allocated) {
            Purchase* temp = new Purchase[this->allocated];

            for (int i = 0; i < this->size; i++) {
                temp[i] = this->purchases[i];
            }

            delete[] this->purchases;
            this->allocated *= 2;
            this->purchases = new Purchase[allocated];

            for (int i = 0; i < this->size; i++) {
                this->purchases[i] = temp[i];
            }

            delete[] temp;
        }
        this->purchases[size++] = new_purchase;
//        this->purchases[size - 1].price += this->purchases[size - 1].price * 0.0875;
    }

   else {
        this->UpdatePurchase(new_purchase.item, new_purchase);
    }
}

//O(1)
void wholesalegroup::Member::AddPurchase(const string &item, double price, string date, int quantity) {
    Purchase new_purchase = {item, quantity, price, price * quantity, date};
    this->AddPurchase(new_purchase);
}

//O(1)
void wholesalegroup::Member::UpdatePurchase(const string &item, const Purchase &purchase) {
    this->operator[](item) = purchase;
//    this->operator[](item).price += this->operator[](item).price * 0.0875;
}

//O(1)
void wholesalegroup::Member::UpdatePurchase(const string &item, double new_price, string date, int new_quantity) {
    Purchase new_purchase = {item, new_quantity, new_price, new_price * new_quantity, date};
    this->UpdatePurchase(item, new_purchase);
}

//O(1)
void wholesalegroup::Member::SetQuantity(const string &item, int new_quantity) {
    this->operator[](item).quantity = new_quantity;
    this->operator[](item).total = this->operator[](item).price * this->operator[](item).quantity;
}

//O(1)
void wholesalegroup::Member::SetPrice(const string item, int new_price) {
//    this->operator[](item).price = new_price + (new_price * 0.0875);
    this->operator[](item).total = this->operator[](item).price * this->operator[](item).quantity;
}

//O(1)
void wholesalegroup::Member::ChangeItemName(const string &old_item_name, const string &new_item_name) {
   this->operator[](old_item_name).item = new_item_name;
}

//O(n^2)
void wholesalegroup::Member::calcExpDate(const string &joinDate) {
    assert(joinDate.length() == 10);

    string expDateCopy;
    int tempInt;
    int j;
    string tempStr;

    expDateCopy = joinDate;
    j = 0;

    tempInt = stoi(expDateCopy.substr(6, 9));
    tempInt++;
    tempStr = to_string(tempInt);

    for (unsigned int i = expDateCopy.length() - 4; i < expDateCopy.length(); i++) {
        expDateCopy[i] = tempStr[j];
        j++;
    }

    this->info.expDate = expDateCopy;
}

//O(1)
void wholesalegroup::Member::setPurchaseDate(const string &item, const string &date) {
    this->operator[](item).date = date;
}

//O(1)
wholesalegroup::Member::~Member() {
    delete[] this->purchases;
}
