
#include "Player.h"
#include "Moderator.h"
#include "King.h"
#include <iostream>

King::King()
{
    std::list<Player*> Inferno = *new std::list<Player*>();
    std::list<Player*> Brigands= *new std::list<Player*>();
    std::list<Player*> Populus= *new std::list<Player*>();
    std::list<Moderator*> Aristocracy= *new std::list<Moderator*>();
    //ctor
}

King::~King()
{
    //dtor
}

void King::banPlayerForTime(Player* playerToBan, int durationInSeconds)
{
    playerToBan->bannedForSeconds = durationInSeconds * abs(playerToBan->getTotalDharma());
    playerToBan->addDharma(abs(playerToBan->getDharma()));
    Populus.remove(playerToBan);
    Brigands.push_back(playerToBan);
    //  std::cout<<"King: Ban "<<playerToBan->name << " for "<< (durationInSeconds * abs(playerToBan->getDharma()))<< " Second(s)" <<std::endl;

};

bool King::requestPermanentBan(Player* accused, Moderator* judicator, Player* bondsman)
{

    if ((judicator == nullptr || judicator->getJudgmentOnPlayer(accused))
            && (bondsman == nullptr || !bondsman->bailForPlayer(accused)))
    {

        //std::cout("King: PermaBan "<<accused->name << " for life with reward x in Dharma for finders among the new population.");

        //guilty
        Inferno.push_back(accused);
        Populus.remove(accused);
        accused->permaBanned = true;
    }

    return true;
};


void King::audience( int milliSecondsPast)
{
    Populus.unique();
    Aristocracy.unique();

    for (Moderator* aristocrat: Aristocracy)
    {
        aristocrat->checkForHierarchyConsistency();
    }

    surveyBrigands( ((float)milliSecondsPast)/1000.0);

    banBrigands();

};



void King::surveyBrigands(float timePassedInSeconds)
{
    std::list<Player*> brigandsToPardon;
    for (Player* guilty :  Brigands)
    {
        guilty->bannedForSeconds =   guilty->bannedForSeconds  +  (int) (timePassedInSeconds + 0.5);
        if (guilty->bannedForSeconds >= 0)
        {
            brigandsToPardon.push_back(guilty);
            //  std::cout<<" King: Brigand " << guilty->name <<" pardoned"<<std::endl;
            //redeemed player

        }
    }
    for (Player* subject :  brigandsToPardon)
    {
        Populus.push_back(subject);
        Brigands.remove(subject);
    }
}

void King::banBrigands()
{
    if (Populus.empty())return;


    bool bannedABrigand=false;
    std::list<Player*> brigandsToBan;

    for (Player* subject :  Populus)
    {
        if (subject->getDharma() < 0 && subject->bannedForSeconds <= 0 )
        {
            brigandsToBan.push_back(subject);
        }
    }

    if (brigandsToBan.empty()) return;

    for (Player* subject :  brigandsToBan)
    {
        subject->strikes++;
        if( subject->strikes > 3)
        {
            requestPermanentBan(subject, Aristocracy.front(), subject->thane );
        }
        else
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
}

void King::lowerToComoner(Moderator* nowComoner)
{
    Populus.push_back(nowComoner->player);
    Aristocracy.remove(nowComoner);
    delete(nowComoner);
}

void King::moderatorInsteadOfTheModerator( Moderator * toBeReplaced, Player * replacement)
{

    for (Player* subject :  toBeReplaced->player->lehnsmannList)
    {
        replacement->lehnsmannList.push_back(subject);
    }
    toBeReplaced->player->lehnsmannList.clear();
    lowerToComoner(toBeReplaced);
    riseAKnight(replacement);
};

void King::registerPlayer(Player* player)
{
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
