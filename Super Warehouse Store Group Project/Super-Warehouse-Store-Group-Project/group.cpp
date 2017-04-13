//V 1.3.3.7

#include "group.h"
#include <iostream>
#include <fstream>

using namespace std;

/**********************************************************
 *
 * group
 *_________________________________________________________
 * default ctr
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * memberList: a sequence of members
 * inventory_cap: capacity of the inventory
 * inventory_sz: sz of the inventory
 * ItemNames: array of item names
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

group::group()
{
    memberList.start();
    initialize_members();

    inventory_cap = 1;
    inventory_sz = 0;
    ItemNames = new string[inventory_cap];
    initialize_inventory();
    sort_inventory();
}

/**********************************************************
 *
 * initialize_day
 *_________________________________________________________
 * initializes a particular day's information from a txt file
 *_________________________________________________________
 * PRE-CONDITIONS
 * The following will need defined values
 * fileName: need an input for file name
 * valid: need a bool for validation/error checking
 * memberList: needs to have a member list
 *
 * POST-CONDITIONS
 * n/a
 **********************************************************/

void group::initialize_day(string fileName, bool &valid)
{
    string inFileName = fileName + ".txt";
    ifstream dataIn;
    string line;
    dataIn.open(inFileName);
    if(!dataIn.is_open()){
        valid = false;
    }
    else
    {
        string purchaseDate;
        int id;
        string itemName;
        double itemCost;
        int itemQuantity;
        int index;

        while(getline(dataIn, line))
        {
            purchaseDate = line;
            getline(dataIn, line);
            id = stoi(line);
            getline(dataIn, line);
            itemName = line;
            dataIn >> itemCost >> itemQuantity;
            dataIn.ignore(256, '\n');
            index = memberList.find_user(id);
            if(index != -1){
                wholesalegroup::Purchase newItem;
                newItem.item = itemName;
                newItem.price = itemCost;
                newItem.quantity = itemQuantity;
                newItem.total = itemCost * itemQuantity;
                newItem.date = purchaseDate;
                memberList[index]->AddPurchase(newItem);
                add_item(itemName);
            }
        }
    }
}

void group::initialize_members()
{
    string inFileName = "warehouse shoppers.txt";
    ifstream dataIn;

    string line;

    string name;
    int id;
    wholesalegroup::Membership mem_type;
    string date;

    dataIn.open(inFileName);
        while (getline(dataIn, line)){

            name = line;
            getline(dataIn, line);
            id = stoi(line);
            getline(dataIn, line);
                if (line == "Preferred"){
                    mem_type = wholesalegroup::preferred;
                }else{
                    mem_type = wholesalegroup::basic;
                }
            getline(dataIn, line);
                date = line;

            wholesalegroup::Member *new_member = new wholesalegroup::Member(id, name, mem_type, date);
            memberList.add_member(new_member);

        }
    dataIn.close();

    memberList.sort();
}

string group::printRebates()
{
    string output_str;
    int ID = 0;
    string name;
    double rebateAmount = 0;

    memberList.sort();
    memberList.start();
    while(memberList.is_item())
    {

        if (memberList.current()->GetType() == wholesalegroup::preferred)
        {
            rebateAmount = memberList.current()->getRebateAmount();
            // display to username & ID to as well as rebate amount to ui
            output_str += std::to_string(memberList.current()->GetId());
            output_str += " ";
            output_str += memberList.current()->GetName();
            output_str += " \nRebate Owed : ";
            output_str += std::to_string(rebateAmount);
            output_str += "\n\n";
        }
        memberList.advance();
    }
    return output_str;
}

string group::printMembershipDues()
{
    string output_str;
    int ID = 0;
    string name;
    double dues = 0;

    memberList.sort();
    memberList.sortByPref();
    memberList.start();
    while(memberList.is_item())
    {
        dues = memberList.current()->getDues();
        // Display to UI
        output_str += std::to_string(memberList.current()->GetId());
        output_str += " ";
        output_str += memberList.current()->GetName();
        output_str += " \nMembership Payed Per Year : ";
        output_str += std::to_string(dues);
        output_str += "\n\n";

        memberList.advance();
    }
    return output_str;
}

string group::printExpirations(string month, bool &valid)
{
    string expDateCopy;
    int tempInt;
    string monthStr = month;
    double dues = 0;
    string output_str;
    for(int i=0; i<month.size(); i++)
    {
        monthStr[i] = toupper(monthStr[i]);
    }
    int monthNum = 0;
    if(monthStr == ("JANUARY"))
        monthNum = 1;
    else if(monthStr == ("FEBRUARY"))
        monthNum = 2;
    else if(monthStr == ("MARCH"))
        monthNum = 3;
    else if(monthStr == ("APRIL"))
        monthNum = 4;
    else if(monthStr == ("MAY"))
        monthNum = 5;
    else if(monthStr == ("JUNE"))
        monthNum = 6;
    else if(monthStr == ("JULY"))
        monthNum = 7;
    else if(monthStr == ("AUGUST"))
        monthNum = 8;
    else if(monthStr == ("SEPTEMBER"))
        monthNum = 9;
    else if(monthStr == ("OCTOBER"))
        monthNum = 10;
    else if(monthStr == ("NOVEMBER"))
        monthNum = 11;
    else if(monthStr == ("DECEMBER"))
        monthNum = 12;
    else
        valid = false;
    memberList.sort();
    memberList.start();
    while(memberList.is_item())
    {
        dues = memberList.current()->getDues();
        expDateCopy = memberList.current()->GetExpDate();
        tempInt = stoi(expDateCopy.substr(0, 2));
        if(tempInt == monthNum){
            output_str += std::to_string(memberList.current()->GetId());
            output_str += " ";
            output_str += memberList.current()->GetName();
            output_str += " \nDues amount : ";
            output_str += std::to_string(memberList.current()->getDues());
            output_str += "\n\n";
        }
        memberList.advance();
    }
    return output_str;
}

bool group::checkUpgrade_state(string input_str, bool &valid)
{
    int id;
    string id_str;
    int i = 0;
    bool answer = false;

        //id read as single input
        //store id, check 0-9
        while (input_str[i] != NULL){
                if ( (input_str[i] > 47) && (input_str[i] < 58) ){
                    id_str += input_str[i];
                }else{
                    valid = false;
                }
            i++;
        }
        if (id_str.empty()){
            valid = false;
        }
        if (valid){
            id = stoi(id_str);
            answer = memberList.checkUpgrade(id);
        }
    return answer;
}

bool group::checkDowngrade_state(string input_str, bool &valid)
{
    int id;
    string id_str;
    int i = 0;
    bool answer = false;

        //id read as single input
        //store id, check 0-9
        while (input_str[i] != NULL){
                if ( (input_str[i] > 47) && (input_str[i] < 58) ){
                    id_str += input_str[i];
                }else{
                    valid = false;
                }
            i++;
        }
        if (id_str.empty()){
            valid = false;
        }
        if (valid){
            id = stoi(id_str);
            answer = memberList.checkDowngrade(id);
        }
    return answer;
}

void group::add_member_state(string input_str, bool &valid)
{
    wholesalegroup::Membership mem_type;
    int id;
    string id_str;
    string name;
    int i = 0;

        //id and names read in format: id/name
        //store id, check 0-9
        while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
                if ( (input_str[i] > 47) && (input_str[i] < 58) ){
                    id_str += input_str[i];
                }else{
                    valid = false;
                }
            i++;
        }
    i++;
        //store name, check a-z and A-Z
        while ( (input_str[i] != '/') && (input_str[i] != NULL) ){
                if ( ((input_str[i] > 64) && (input_str[i] < 91))
                     || ((input_str[i] > 96) && (input_str[i] < 123)) ){
                    name += input_str[i];
                }else{
                    valid = false;
                }
            i++;
        }
    i++;
        //store member type
        if (input_str[i] == 'b'){
            mem_type = wholesalegroup::basic;
        }else if (input_str[i] == 'p'){
            mem_type = wholesalegroup::preferred;
        }else{
            valid = false;
        }

        if ( (id_str.empty()) || (name.empty()) ){
            valid = false;
        }
        if (valid){
            id = stoi(id_str);
            wholesalegroup::Member *member_ptr = new wholesalegroup::Member(id, name, mem_type);
            memberList.add_member(member_ptr);
            memberList.sort();
        }
}

void group::remove_member_state(string input_str, bool &valid)
{
    int id;
    string id_str;
    int i = 0;

        //id read as single input
        //store id, check 0-9
        while (input_str[i] != NULL){
                if ( (input_str[i] > 47) && (input_str[i] < 58) ){
                    id_str += input_str[i];
                }else{
                    valid = false;
                }
            i++;
        }
        if (id_str.empty()){
            valid = false;
        }
        if (valid){
            id = stoi(id_str);
            memberList.remove_member(id);
        }
}

void group::purchase_history_state(string input_str, bool &valid, int &target_index, string &input_Type)
{
    int id;
    string id_str;
    string name;
    int i = 0;

        //check if name or id was input, then set input_type
        if ( ((input_str[i] > 64) && (input_str[i] < 91))
             || ((input_str[i] > 96) && (input_str[i] < 123)) ){
            input_Type = "NAME";
        }else{
            input_Type = "ID";
        }

        //gather name/id info

        //mode is ID
        if (input_Type == "ID"){
            while (input_str[i] != NULL){
                    if ( (input_str[i] > 47) && (input_str[i] < 58) ){
                        id_str += input_str[i];
                    }else{
                        valid = false;
                    }
                i++;
            }
            if (id_str.empty()){
                valid = false;
            }
            if (valid){
                id = stoi(id_str);
                target_index = memberList.find_user(id);
            }

        //mode is NAME
        }else{
            //store name, check a-z and A-Z
            while (input_str[i] != NULL){
                    if ( ((input_str[i] > 64) && (input_str[i] < 91))
                         || ((input_str[i] > 96) && (input_str[i] < 123)) ){
                        name += input_str[i];
                    }else{
                        valid = false;
                    }
                i++;
            }

            if (name.empty()){
                valid = false;
            }
            if (valid){
                target_index = memberList.find_user(name);
            }
        }
}

void group::purchase_history_special_state(string input_str, bool &valid, int &target_index)
{
    int id;
    string id_str;
    int i = 0;

        //id read as single input
        //store id, check 0-9
        while (input_str[i] != NULL){
                if ( (input_str[i] > 47) && (input_str[i] < 58) ){
                    id_str += input_str[i];
                }else{
                    valid = false;
                }
            i++;
        }
        if (id_str.empty()){
            valid = false;
        }
        if (valid){
            id = stoi(id_str);
            target_index = memberList.find_user(id);
        }
}

string group::get_Member_Purchases_String(int index){
    //purchase history lookup, one function for id, one for name
    int id = memberList[index]->GetId();
    string name = memberList[index]->GetName();

    string output_Str;
    output_Str += "ID: "; output_Str += std::to_string(id); output_Str += "    ";
    output_Str += "NAME: "; output_Str += name; output_Str += "    ";

    output_Str += "MEMBERSHIP: ";
    if (memberList[index]->GetType() == wholesalegroup::basic){
        output_Str += "Basic"; output_Str += "\n";
    }else{
        output_Str += "Preferred"; output_Str += "\n";
    }

        for (int i = 0; i < memberList[index]->PurchaseLen(); i++){
            output_Str += "   Item: "; output_Str += (*memberList[index])[i].item; output_Str += "\n";
            output_Str += "   Quantity: "; output_Str += std::to_string((*memberList[index])[i].quantity); output_Str += "\n";
            output_Str += "   Price: $"; output_Str += std::to_string((*memberList[index])[i].price); output_Str += "\n";
            output_Str += "   Total: $"; output_Str += std::to_string((*memberList[index])[i].total); output_Str += "\n";
            output_Str += "\n";
        }
        if (memberList[index]->PurchaseLen() == 0){
            output_Str += "   No Purchase History"; output_Str += "\n";
        }
    return output_Str;
}

string group::get_Members_String()
{
    int id;
    string name;
    string date;
    string output_Str;

        for (int i = 0; i < memberList.size(); i++){
            id = memberList[i]->GetId();
            name = memberList[i]->GetName();
            date = memberList[i]->GetExpDate();

            output_Str += "ID: "; output_Str += std::to_string(id); output_Str += "    ";
            output_Str += "NAME: "; output_Str += name; output_Str += "    ";

            output_Str += "MEMBERSHIP: ";
                if (memberList[i]->GetType() == wholesalegroup::basic){
                    output_Str += "Basic";
                }else{
                    output_Str += "Preferred";
                }

            output_Str += "    "; output_Str += "EXP_DATE: "; output_Str += date; output_Str += "\n";
        }

    return output_Str;
}

void group::printItemInfo(string &itemName, int &quantity, double &price, bool &valid)
{
    valid = false;
    memberList.start();
    while(memberList.is_item())
    {
        if (itemName == memberList.current()->GetPurchase(itemName).item)
        {
            quantity += memberList.current()->GetPurchase(itemName).quantity;
            price = memberList.current()->GetPurchase(itemName).price;
            valid = true;
        }
        memberList.advance();
    }
}

void group::sort_inventory()
{
    int i_low;
        for (int i = 0; i < inventory_sz; i++){
            i_low = i;
            for (int j = i; j < inventory_sz; j++){
                if (ItemNames[j] < ItemNames[i_low]){
                    i_low = j;
                }
            }
            swap(ItemNames[i], ItemNames[i_low]);
        }
}

void group::expand_inventory()
{
    inventory_cap *= 2;
    string *newItems = new string[inventory_cap];

    copy(ItemNames, ItemNames + (inventory_sz - 1), newItems);

    delete [] ItemNames;
    ItemNames = newItems;
}

bool group::inventory_contains(string input)
{
        for (int i = 0; i < inventory_sz; i++){
            if (ItemNames[i] == input){
                return true;
            }
        }
    return false;
}

void group::add_item(string input)
{
    //no duplicates allowed
    if (!inventory_contains(input)){
        inventory_sz++;
            if (inventory_sz > inventory_cap){
                expand_inventory();
            }
        ItemNames[inventory_sz - 1] = input;
    }
    //if duplicate, do nothing
}

void group::initialize_inventory()
{
    //scan everyone
    for (int i = 0; i < memberList.size(); i++)
    {
        //scan everyone's purchases
        for (int j = 0; j < memberList[i]->PurchaseLen(); j++){
            add_item((*memberList[i])[j].item);
        }
    }
}

string group::get_All_Purchases_String()
{
    memberList.sort();
    string output_Str;
    double total = 0;

        for (int i = 0; i < memberList.size(); i++){
            for (int j = 0; j < memberList[i]->PurchaseLen(); j++){
                total += (*memberList[i])[j].total;
            }

            output_Str += get_Member_Purchases_String(i);
            output_Str += "\n";
        }

    output_Str += "Total Revenue: "; output_Str += to_string(total + total * 0.0875); output_Str += "\n";

    return output_Str;
}

string group::get_Quantities_Sold_String()
{
    string output_Str;

    int quantity;
    double price;
    bool valid;

    for (int i = 0; i < inventory_sz; i++){
        quantity = 0;
        price = 0;
        printItemInfo(ItemNames[i], quantity, price, valid);
        output_Str += ItemNames[i]; output_Str += "    qty: ";
        output_Str += to_string(quantity); output_Str += "\n";
    }


    return output_Str;
}


string group::dailySalesReport(string dayDate, bool &valid)
{
    string output_str;      // Overall string to be sent back

    string ItemQuantityArray[20][2];        // 2D array with item and accompanying quantity
    string DailyCustomerList[20];       // array of customers who shopped this day
    //Initializing both the arrays
    for (int i = 0; i < 20; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            ItemQuantityArray[i][j] = "?";
        }
        DailyCustomerList[i] = "?";
    }
    double totalRevenue = 0;            // total revenue
    int prefCount = 0;
    int basicCount = 0;

    string inFileName = dayDate + ".txt";
    ifstream dataIn;
    string line;
    dataIn.open(inFileName);
    if(!dataIn.is_open()){
        valid = false;
    }
    else
    {
        // Filled from the file
        string purchaseDate;
        int id;
        string itemName;
        double itemCost;
        int itemQuantity;
        // Indirect filled
        int index;
        string CustomerName;
        bool isBasic;

        while(getline(dataIn, line))
        {
            // Info Gathering from File
            purchaseDate = line;
            getline(dataIn,line);
            id = stoi(line);
            getline(dataIn, line);
            itemName = line;
            dataIn >> itemCost >> itemQuantity;
            dataIn.ignore(256,'\n');
            // Things filled in INDIRECTLY from the file
            index = memberList.find_user(id);
            totalRevenue += itemCost * itemQuantity;

            // Finds the name associated with the id and set/unset basic flag
            memberList.start();
            while(memberList.is_item())
            {
                if(memberList.current()->GetId() == id)
                {
                    CustomerName = memberList.current()->GetName();
                    // Determine if basic or not
                    if (memberList.current()->GetType() == wholesalegroup::basic)
                        isBasic = true;
                    else
                        isBasic = false;
                    break;
                }
                else
                    memberList.advance();
            }
            // Places Name into array
            for(int i = 0; i < 20; i++)
            {
                if (DailyCustomerList[i] == "?")
                {
                    DailyCustomerList[i] = CustomerName;
                    break;
                }
                if (DailyCustomerList[i] == CustomerName)
                    break;
            }

            // Fill the 2D array with name and quantity if not found. Add quantity if found.
            // Break for each! Also update basic/pref count if new entry
            for (int i = 0; i < 20; i++)
            {
                if (ItemQuantityArray[i][0] == "?")
                {
                    ItemQuantityArray[i][0] = itemName;
                    ItemQuantityArray[i][1] = to_string(itemQuantity);
                    if (isBasic)
                        basicCount++;
                    else
                        prefCount++;
                    break;
                }
                if (ItemQuantityArray[i][0] == itemName)
                {
                    int sumQuantity = itemQuantity + stoi(ItemQuantityArray[i][1]);
                    ItemQuantityArray[i][1] = to_string(sumQuantity);
                    break;
                }
            }
        }
        //Outside whileloop
        //Place info in string to be read as report
        output_str += "Daily Sales Report\n";
        // Item and Quantity
        for (int i = 0; i < 20; i++)
        {
            if (ItemQuantityArray[i][0] != "?")
            {
                output_str += to_string(i) + ") ";
                output_str += ItemQuantityArray[i][0];
                output_str += "\nQuantity Sold:";
                output_str += ItemQuantityArray[i][1];
                output_str += "\n";
            }
        }
        // Members who shopped that day
        output_str += "\nMembers who shoppped here today.\n";
        for (int i = 0; i < 20; i++)
        {
            if (DailyCustomerList[i] != "?")
            {
                output_str += to_string(i) + ") ";
                output_str += DailyCustomerList[i];
                output_str += "\n";
            }
        }
        // Total Revenue
        output_str += "\nTotal Revenue Earned Today : $";
        output_str += to_string(totalRevenue);
        output_str += "\n";
        // Preferred and Basic Totals
        output_str += "\nNumber of Preferred Shoppers Today : ";
        output_str += to_string(prefCount);
        output_str += "\nNumber of Basic Shoppers Today : ";
        output_str += to_string(basicCount);
        output_str += "\n";
    }
    return output_str;
}



