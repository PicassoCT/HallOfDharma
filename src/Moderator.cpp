
#include "Player.h"
#include "King.h"
#include "Moderator.h"

Moderator::Moderator(Player* riseAKnigth, King* king)
{
    this->player = riseAKnigth;
    this->king = king;
    //ctor
}


/** Default destructor */
Moderator::~Moderator()
{
};



bool Moderator::banLehnsmann(Player* playerToBan, int durationInMinutes)
{
    for (Player* lehnsmann :  player->lehnsmannList)
    {
        if ( lehnsmann == playerToBan)
        {
            king->banPlayerForTime(playerToBan, durationInMinutes);
            player->lehnsmannList.remove(playerToBan);
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
    if (player->lehnsmannList.empty())
    {
        king->lowerToComoner(this);
        return;
    }

    for (Player* lehnsmann :  player->lehnsmannList)
    {
        if (this->player->getDharma() < lehnsmann->getDharma())
        {
            king->moderatorInsteadOfTheModerator(this,lehnsmann);
        }
    }

};




bool Moderator::getJudgmentOnPlayer(Player* accused)
{
    return accused->getTotalDharma() < this->player->getTotalDharma();
} //TODO Get better judgement


