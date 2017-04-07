//v1.3.8
#include "group.h"

group::group()
{
    memberList.start();


    ///**REMOVE ALL THIS WHEN NO LONGER TESTING!!!!!
    ///**THIS WILL PRE LOAD 6 PEOPLE INTO MEMBER LIST
    wholesalegroup::Member *mem1 = new wholesalegroup::Member(123, "andy");
    memberList.add_member(mem1);

    wholesalegroup::Member *mem2 = new wholesalegroup::Member(456, "damon", wholesalegroup::preferred);
    memberList.add_member(mem2);

    wholesalegroup::Member *mem3 = new wholesalegroup::Member(789, "kit");
    memberList.add_member(mem3);

    wholesalegroup::Member *mem4 = new wholesalegroup::Member(133, "armen", wholesalegroup::preferred);
    memberList.add_member(mem4);

    wholesalegroup::Member *mem5 = new wholesalegroup::Member(144, "eeeeeee");
    memberList.add_member(mem5);

    wholesalegroup::Member *mem6 = new wholesalegroup::Member(155, "kit", wholesalegroup::preferred);
    memberList.add_member(mem6);



           ///***********testing add purchases, remove when done testing
            wholesalegroup::Purchase newPurchase;
            newPurchase.item = "apple";
            newPurchase.quantity = 3;
            newPurchase.price = 3.45;
            newPurchase.total = 20.54;
            memberList[2]->AddPurchase(newPurchase);

            wholesalegroup::Purchase newPurchase2;
            newPurchase2.item = "cake";
            newPurchase2.quantity = 9;
            newPurchase2.price = 20.34;
            newPurchase2.total = 304.67;
            memberList[2]->AddPurchase(newPurchase2);
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

void group::printExpirations(string month)
{
    Sequence expireList;
    memberList.start();
    while(memberList.current())
    {
        //incomplete date comparison, fix later
        if(memberList.current()->GetExpDate() == month)
        {
//            expireList.insert(new Member(memberList.current()->GetInfo()));
        }
        memberList.advance();
    }
    //display expire list in GUI
    expireList.start();
    //finish this when GUI implemented
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
    string output_Str;

        for (int i = 0; i < memberList.size(); i++){
            id = memberList[i]->GetId();
            name = memberList[i]->GetName();

            output_Str += "ID: "; output_Str += std::to_string(id); output_Str += "    ";
            output_Str += "NAME: "; output_Str += name; output_Str += "    ";

            output_Str += "MEMBERSHIP: ";
                if (memberList[i]->GetType() == wholesalegroup::basic){
                    output_Str += "Basic"; output_Str += "\n";
                }else{
                    output_Str += "Preferred"; output_Str += "\n";
                }
        }

    return output_Str;
}
///***END OF NEW FUNCTIONS IN THIS VERSION
