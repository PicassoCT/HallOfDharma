#include "Moderator.h"

Moderator::Moderator(Player* riseAKnigth, King* king)
{
    Player* innerClass;
    innerClass = this->getPlayer();
    *innerClass = *riseAKnigth;
    this->king = king;
    //ctor
}

Moderator::~Moderator()
{
    //dtor
}

bool Moderator::banLehnsmann(Player* playerToBan, int durationInMinutes)
{
    for (Player* lehnsmann :  lehnsmannList)
    {
        if ( lehnsmann == playerToBan)
        {
            king->banPlayerForTime(playerToBan, durationInMinutes);
            lehnsmannList.remove(playerToBan);
        }
    }
    return true;
}

bool Moderator::requestPermaBan(Player* accused, Moderator* judicator, Player* bondsman)
{
    return  king->requestPermanentBan( accused, judicator, bondsman);
}

/** Check for Feudal Consistency */
void Moderator::checkForHierarchyConsistency(void)
{
    if (lehnsmannList.empty())
    {
        king->setFree(this);
        return;
    }

    for (Player* lehnsmann :  lehnsmannList)
    {
        if (this->getDharma() < lehnsmann->getDharma())
        {
            king->moderatorInsteadOfTheModerator(this,lehnsmann);
        }
    }

};

void Moderator::moderatorInsteadOfTheModerator(Moderator *oldOne, Player * newOne, King* KingToReportTo)
{
}
