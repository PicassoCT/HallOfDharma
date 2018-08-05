
#include "Player.h"
#include "King.h"
#include "Moderator.h"

Moderator::Moderator(Player* riseAKnigth, King* king)
{
    Player* innerClass;
    innerClass = this->getPlayer();
    *innerClass = *riseAKnigth;
    this->king = king;
    //ctor
}


/** Default destructor */
Moderator::~Moderator()
{
     delete(this->getPlayer());
};



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
        king->registerPlayer(this);
        return;
    }

    for (Player* lehnsmann :  lehnsmannList)
    {
        if (this->getDharma() < lehnsmann->getDharma())
        {
            king->moderatorInsteadOfTheModerator(this,lehnsmann, this->getPlayer(), lehnsmann);
        }
    }

};

void Moderator::informLehnsmannOfReplacement(Moderator* newThane)
{
    for (Player* lehnsmann :  lehnsmannList)
    {
        lehnsmann->swareToThane(newThane);
    }
}


bool Moderator::getJudgmentOnPlayer(Player* accused)
{
    return accused->getTotalDharma() < this->getTotalDharma();
} //TODO Get better judgement


