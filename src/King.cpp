
#include "Player.h"
#include "Moderator.h"
#include "King.h"
#include <iostream>

King::King()
{
    //ctor
}

King::~King()
{
    //dtor
}





void King::banPlayerForTime(Player* playerToBan, int durationInSeconds)
{
    std::cout<<"Audience: Ban "<<playerToBan->name << " for "<< (durationInSeconds * abs(playerToBan->getDharma()))<< " Second(s)" <<std::endl;
    playerToBan->bannedForSeconds = durationInSeconds * abs(playerToBan->getDharma());
    playerToBan->addDharma(abs(playerToBan->getDharma()));
    Populus.remove(playerToBan);
    Brigands.push_back(playerToBan);
};

bool King::requestPermanentBan(Player* accused, Moderator* judicator, Player* bondsman)
{

    if (judicator->getJudgmentOnPlayer(accused) && !bondsman->bailForPlayer(accused))
    {
        //guilty
        Inferno.push_back(accused);
        Populus.remove(accused);
        accused->permaBanned = true;
    }

    return true;
};


void King::audience( int milliSecondsPast)
{

    for (Moderator* aristocrat: Aristocracy) {
        aristocrat->checkForHierarchyConsistency();
    }

    surveyBrigands( ((float)milliSecondsPast)/1000.0);

    banBrigands();

};

void King::surveyBrigands(float timePassedInSeconds)
{
    for (Player* guilty :  Brigands)
    {
        guilty->bannedForSeconds =   guilty->bannedForSeconds  +  (int) (timePassedInSeconds + 0.5);
        if (guilty->bannedForSeconds >= 0)
        {
               std::cout<<" Royal Audience:" << guilty->name <<" reinstated!"<<std::endl;
            //redeemed player
            Populus.push_back(guilty);
            Brigands.remove(guilty);
        }
    }
}

void King::banBrigands()
{
    for (Player* subject :  Populus)
    {
        if (subject->getDharma() < 0)
        {
            banPlayerForTime(subject, abs(subject->getDharma()));

        }
    }
}

void King::riseAKnight(Player* newNoble)
{
    Moderator* newModerator = new Moderator(newNoble,this);
    Aristocracy.push_back(newModerator);
    Populus.remove(newNoble);
    delete(newNoble);



}

void King::moderatorInsteadOfTheModerator( Moderator * toBeReplaced, Player * replacement, Player* toBeReplacedPlayer, Player* replacementModerator)
{
    Player* newPlayer = new Player(toBeReplaced->name, this);
    *newPlayer = *toBeReplaced->getPlayer();
    Populus.push_back(newPlayer);
    Aristocracy.remove(toBeReplaced);


    Moderator* newModerator = new Moderator(replacement,this);
    Aristocracy.push_back(newModerator);
    Populus.remove(replacement);

    toBeReplaced->swareToThane(newModerator);
    newPlayer ->swareToThane(newModerator);

    delete (toBeReplaced);
    delete(replacement);

};

void King::registerPlayer(Player* player)
{
    bool allreadyRegistered = false;
    for (Player* subject :  Populus)
    {
        if (subject == player)
        {
            return;
        }
    }
    Populus.push_back(player);
};

void King::removePlayer(Player* player)
{
    Populus.remove(player);
};
