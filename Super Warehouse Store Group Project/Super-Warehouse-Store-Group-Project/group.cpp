//v1.4.11
#include "group.h"

#include <fstream>

using namespace std;

group::group()
{
    memberList.start();
    initialize_members();
}

void group::initialize_members()
{
    string inFileName = "warehouse shoppers.txt";
    ifstream dataIn;

    string line;
    int i = 0;

    string name;                            // i = 0
    int id;                                 // i = 1
    wholesalegroup::Membership mem_type;    // i = 2
    string date;                            // i = 3

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

///***ALL NEW FUNCTIONS IN THIS VERSION DEFINED BELOW
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
///***END OF NEW FUNCTIONS IN THIS VERSION
