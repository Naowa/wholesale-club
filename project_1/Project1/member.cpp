#include <cassert>

#include "member.h"

using std::string;

wholesalegroup::Member::Member(int id, const std::string &name, Membership type) {
    this->info.id = id;
    this->info.name = name;
    this->info.type = type;
    this->size = 0;
    this->allocated = 10;

    purchases = new Purchase[this->allocated];
}

wholesalegroup::Member::Member(MemberInfo info) {
    this->info = info;
}


wholesalegroup::Purchase& wholesalegroup::Member::GetPurchase(const string &item) const {
    for (int i = 0; i < size; i++) {
        if (this->purchases[i].item == item) {
            return this->purchases[i];
        }
    }

    return this->purchases[0]; //this would count as an error
}

wholesalegroup::Purchase& wholesalegroup::Member::operator[](const string &item) const {
    return this->GetPurchase(item);
}

wholesalegroup::Purchase& wholesalegroup::Member::operator[](int index) const {
    assert(index < this->PurchaseLen());

    return this->purchases[index];
}

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

void wholesalegroup::Member::AddPurchase(const string &item, double price, int quantity) {
    Purchase new_purchase = {item, quantity, price, price * quantity};
    this->AddPurchase(new_purchase);
}


void wholesalegroup::Member::UpdatePurchase(const string &item, const Purchase &purchase) {
    this->operator[](item) = purchase;
}

void wholesalegroup::Member::UpdatePurchase(const string &item, int new_quantity, double new_price) {
    Purchase new_purchase = {item, new_quantity, new_price, new_price * new_quantity};
    this->UpdatePurchase(item, new_purchase);
}

void wholesalegroup::Member::SetQuantity(const string &item, int new_quantity) {
    this->operator[](item).quantity = new_quantity;
    this->operator[](item).total = this->operator[](item).price * this->operator[](item).quantity;
}

void wholesalegroup::Member::SetPrice(const string item, int new_price) {
    this->operator[](item).price = new_price;
    this->operator[](item).total = this->operator[](item).price * this->operator[](item).quantity;
}

void wholesalegroup::Member::ChangeItemName(const string &old_item_name, const string &new_item_name) {
   this->operator[](old_item_name).item = new_item_name;
}


wholesalegroup::Member::~Member() {
    delete[] this->purchases;
}
