//v0.0.3
#include "group.h"

group::group()
{
    memberList.start();
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

bool group::checkUpgrade(value_type m)
{
    //change GetType() to getType() ???
    if(m.GetType() == basic)
    {
        double possibleRebate = m.getAnnualTotal() * .05;
        if(possibleRebate > 15)
        {
            //display in GUI here
            return true;
        }
        //display in GUI here
        return false;
    }
    else
    {
        std::cout << "ERROR. Check upgrade on preferred." << endl;
        return false;
    }
}

bool group::checkDowngrade(value_type m)
{
    if(m.GetType() == premium) // change to preferred after armen changes
    {
        double currentRebate = m.getRebateAmount();
        if(m.getAnnualTotal() - currentRebate < 15)
        {
            //display in GUI here
            return true;
        }
        //display in GUI here
        return false;
    }
    else
    {
        std::cout << "ERROR. Check downgrade on basic." << endl;
        return false;
    }
}
