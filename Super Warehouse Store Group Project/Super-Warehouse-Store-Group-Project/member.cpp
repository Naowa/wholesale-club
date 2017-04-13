//V 1.3.3.7

#include <cassert>
#include <cstdlib>
#include "member.h"

using std::string;
using std::stoi;
using std::to_string;
using std::copy;

/**********************************************************
 *
 * Member - O(n^2)
 *_________________________________________________________
 * full ctr
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * id: unique id for a member
 * name: name of member
 * type: type of membership
 * joinDate: join date of membership
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/
wholesalegroup::Member::Member(int id, const std::string &name, Membership type, string joinDate) {
    this->info.id = id;
    this->info.name = name;
    this->info.type = type;
    this->size = 0;
    this->allocated = 10;

    purchases = new Purchase[this->allocated];

    calcExpDate(joinDate);
}

/**********************************************************
 *
 * Member - O(1)
 *_________________________________________________________
 * initialized ctr
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * info: MemberInfo struct to construct from
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/
wholesalegroup::Member::Member(MemberInfo info) {
    this->info = info;
    purchases = new Purchase[this->allocated];
}

/**********************************************************
 *
 * Member - O(n)
 *_________________________________________________________
 * copy ctr
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * other: other Member to copy from
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/
wholesalegroup::Member::Member(Member& other) {
    this->operator=(other);
}

/**********************************************************
 *
 * operator= - O(n)
 *_________________________________________________________
 * assigns a member to the other member's info
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * other - other member to copy
 *
 * POST-CONDITIONS
 * this member will have its info assigned to the other
 * member's info
 **********************************************************/
void wholesalegroup::Member::operator=(Member& other) {
    this->info = other.info;
    this->allocated = other.allocated;
    this->size = other.size;
    this->purchases = new Purchase[this->allocated];
    copy(other.purchases, other.purchases + allocated, this->purchases);
}

/**********************************************************
 *
 * GetPurchase - O(n)
 *_________________________________________________________
 * returns a pointer to a purchase of a member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item: item to be searched
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/
wholesalegroup::Purchase& wholesalegroup::Member::GetPurchase(const string &item) const {
    for (int i = 0; i < this->size; i++) {
        if (this->purchases[i].item == item) {
            return this->purchases[i];
        }
    }

    return this->purchases[0]; //this would count as an error
}

/**********************************************************
 *
 * getAnnualtotal - O(n)
 *_________________________________________________________
 * returns the annual total spent of a member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * double value returned that is the annual total spent
 **********************************************************/
double wholesalegroup::Member::getAnnualTotal() const {
    double total;

    total = 0;

    for (int i = 0; i < this->size; i++ ) {
        total += this->purchases[i].price;
    }

    return total;
}

/**********************************************************
 *
 * getRebateAmount - O(1)
 *_________________________________________________________
 * returns the rebate amount of a member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * double value returned that is the rebate earned
 **********************************************************/
double wholesalegroup::Member::getRebateAmount() {
    if (this->info.type == basic) {
        return 0;
    }

    return this->getAnnualTotal() * 0.05;
}

/**********************************************************
 *
 * getDues - O(1)
 *_________________________________________________________
 * returns the dues owed by a member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * none
 *
 * POST-CONDITIONS
 * double value returned that is the amount owed for a
 * membership
 **********************************************************/
double wholesalegroup::Member::getDues() const {
    double BASIC_DUES = 60;
    double PREF_DUES = 75;

    if (this->info.type == basic) {
        return BASIC_DUES;
    }

    return PREF_DUES;
}

/**********************************************************
 *
 * getPurchaseDate - O(1)
 *_________________________________________________________
 * returns a pointer to a purchase of a member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item: item to be searched
 *
 * POST-CONDITIONS
 * returns the date as a string in the form MM/DD/YYYY of
 * the date an item was purchased
 **********************************************************/
string wholesalegroup::Member::getPurchaseDate(string& item) const{
    return this->operator[](item).date;
}

/**********************************************************
 *
 * GetPurchase - O(1)
 *_________________________________________________________
 * returns a pointer to a purchase of a member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item: item to be searched
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/
wholesalegroup::Purchase& wholesalegroup::Member::operator[](const string &item) const {
    return this->GetPurchase(item);
}

/**********************************************************
 *
 * operator[] - O(1)
 *_________________________________________________________
 * returns a pointer to a purchase of a member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * index: index of item in the Purchase struct
 *
 * POST-CONDITIONS
 * returns a pointer to a purchase
 **********************************************************/
wholesalegroup::Purchase& wholesalegroup::Member::operator[](int index) const {
    assert(index < this->PurchaseLen());

    return this->purchases[index];
}

/**********************************************************
 *
 * AddPurchase - O(n)
 *_________________________________________________________
 * adds a purchase to the member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * new_purchase: purchase to be added
 *
 * POST-CONDITIONS
 * new purchase added to the member's purchase history
 **********************************************************/
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
    }

   else {
        this->UpdatePurchase(new_purchase.item, new_purchase);
    }
}

/**********************************************************
 *
 * AddPurchase - O(1)
 *_________________________________________________________
 * adds a purchase to the member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item: item name
 * price: price of item
 * date: date of purchase
 * quantity: quantity of item purchased
 *
 * POST-CONDITIONS
 * new purchase added to the member's purchase history
 **********************************************************/
void wholesalegroup::Member::AddPurchase(const string &item, double price, string date, int quantity) {
    Purchase new_purchase = {item, quantity, price, price * quantity, date};
    this->AddPurchase(new_purchase);
}

/**********************************************************
 *
 * UpdatePurhase - O(1)
 *_________________________________________________________
 * updates a purchase for the member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item: item to be updated
 * purchase: purchase holding update info
 *
 * POST-CONDITIONS
 * purchase updated in the member's purchase history
 **********************************************************/
void wholesalegroup::Member::UpdatePurchase(const string &item, const Purchase &purchase) {
    this->operator[](item) = purchase;
}

/**********************************************************
 *
 * UpdatePurhase - O(1)
 *_________________________________________________________
 * updates a purchase for the member
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item: item to be updated
 * new_price: new price of item
 * date: new date of item
 * new_quantity: new quantity of item
 *
 * POST-CONDITIONS
 * purchase updated in the member's purchase history
 **********************************************************/
void wholesalegroup::Member::UpdatePurchase(const string &item, double new_price, string date, int new_quantity) {
    Purchase new_purchase = {item, new_quantity, new_price, new_price * new_quantity, date};
    this->UpdatePurchase(item, new_purchase);
}

/**********************************************************
 *
 * SetQuantity - O(1)
 *_________________________________________________________
 * updates the quantity for an item
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item: item to be updated
 * new_quantity: new quantity of item
 *
 * POST-CONDITIONS
 * item updated in the member's purchase history
 **********************************************************/
void wholesalegroup::Member::SetQuantity(const string &item, int new_quantity) {
    this->operator[](item).quantity = new_quantity;
    this->operator[](item).total = this->operator[](item).price * this->operator[](item).quantity;
}

/**********************************************************
 *
 * SetPrice - O(1)
 *_________________________________________________________
 * updates the price for an item
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item: item to be updated
 * new_price: new price of item
 *
 * POST-CONDITIONS
 * item updated in the member's purchase history
 **********************************************************/
void wholesalegroup::Member::SetPrice(const string item, int new_price) {
    this->operator[](item).total = this->operator[](item).price * this->operator[](item).quantity;
}

/**********************************************************
 *
 * ChangeItemName - O(1)
 *_________________________________________________________
 * updates the name of an item
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * old_item_name: old name to be searched
 * new_item_name: new name to be changed to
 *
 * POST-CONDITIONS
 * item updated in the member's purchase history
 **********************************************************/
void wholesalegroup::Member::ChangeItemName(const string &old_item_name, const string &new_item_name) {
   this->operator[](old_item_name).item = new_item_name;
}

/**********************************************************
 *
 * calcExpDate - O(n^2)
 *_________________________________________________________
 * calculates and sets a member's expiration date
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * joinDate: date of the start of membership
 *
 * POST-CONDITIONS
 * expDate for member is set
 **********************************************************/
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

/**********************************************************
 *
 * SetPurchaseDate - O(1)
 *_________________________________________________________
 * updates the purchase date for an item
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * item: item to be updated
 * date: new date of purchase
 *
 * POST-CONDITIONS
 * item updated in the member's purchase history
 **********************************************************/
void wholesalegroup::Member::setPurchaseDate(const string &item, const string &date) {
    this->operator[](item).date = date;
}

/**********************************************************
 *
 * ~Member - O(1)
 *_________________________________________________________
 * member destructor
 *_________________________________________________________
 * PRE-CONDITIONS
 * none
 *
 * POST-CONDITIONS
 * dynamic memory for member is freed
 **********************************************************/
wholesalegroup::Member::~Member() {
    delete[] this->purchases;
}
