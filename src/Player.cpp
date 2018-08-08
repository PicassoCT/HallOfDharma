#include "Player.h"
#include "Moderator.h"
#include "King.h"

#include <iostream>

Player::Player(std::string name, King* king)
{
    this->king = king;
    m_dharma = 0;
    this->name = name;
    king->registerPlayer(this);
    //ctor
}

Player::~Player()
{
    king->removePlayer(this);
    //dtor
}

int Player::getTotalDharma()
{
    int totalDharma = m_dharma;

    for (Player* lehnsmann :  lehnsmannList)
    {
        totalDharma += lehnsmann->getTotalDharma();
    }
    return totalDharma;
}

Player* Player::getPlayer()
{
    return this;
}

/** Set m_dharma
 * \param val New value to set
 */
void Player::addDharma(int val)
{
    if (this->bannedForSeconds > 0)return;
    m_dharma += val;
  //  std::cout<< "Add Dharma "<< val << " to players "<< this->name << ". Total Dharma: "<< this->getDharma() <<std::endl;

}
void Player::subDharma(int val)
{
    if (this->bannedForSeconds > 0)return;
    m_dharma -= val;
  //   std::cout<< "Sub Dharma "<< val << " from player "<< this->name << ". Total Dharma: "<< this->getDharma() <<std::endl;

}

/** get the dharma of this player standalone
 */
int Player::getDharma()
{
    return m_dharma;
}

/** Get Recruited by another Thane*/
void  Player::swareToThane(Player* thane)
{
    if (this->thane != nullptr)
    {
        this->thane->informOfBetrayal(this, thane);
    }

    if (thane->getDharma() < this->getDharma())
    {
        thane->recruitLehnsmann(this);
        this->thane = thane;
    }
};


/** A Player can recruit other free Lehnsmann- if his kharma is lower*/
void  Player::recruitLehnsmann(Player * lehnsmann)
{
    if (lehnsmann->thane != nullptr || lehnsmann == this || this->thane == lehnsmann ) return;

    if ((lehnsmann->getDharma() < this->getDharma()) &&
            lehnsmann->thane == nullptr)
    {
       // std::cout<<">>>Player  "<< this->name <<" recruited " << lehnsmann->name <<std::endl;

        Recruits.push_back(lehnsmann);
        lehnsmannList.push_back(lehnsmann);

        if (this->thane == nullptr)
        {
            king->riseAKnight(this);
        }
    }

    lehnsmannList.unique();
};

/** A Player can discard any direct lower Lehnsmann and his Followers
    either adding him to another Thane - or setting him free
    Returns: null on move - otherwise a pointer to the player set free
*/
void  Player::disownLehnsmann(Player* lehnsmann, Player *newThane)
{
    if (this == lehnsmann) return;

    //std::cout<<"Player "<< this->name << " : disowned " << lehnsmann->name <<std::endl;
    Player* iDisownYou;

    for (Player* trusted :  Recruits)
    {
        if (trusted == lehnsmann && this != lehnsmann)
        {
            iDisownYou = trusted;
        }
    }

    Recruits.remove(iDisownYou);
    lehnsmannList.remove(iDisownYou);

    if (newThane == nullptr)
    {
        king->registerPlayer(lehnsmann);
        return;
    }
};

void  Player::informOfBetrayal(Player* formerLehnsmann, Player* newThane)
{
    this->disownLehnsmann(formerLehnsmann, newThane);
}

void Player::behaveRational()
{
    for (Player* subject: lehnsmannList)
    {
        if (subject->getTotalDharma() < 0)
            disownLehnsmann(this, nullptr);
    }
}

bool  Player::bailForPlayer(Player* accused)
{
    bool oneOfMine= false;
    for (Player* trusted :  Recruits)
    {
        if (trusted == accused)
        {
            oneOfMine = true;
            break;
        }
    }

    if (oneOfMine   && abs(accused->getDharma()) < getDharma())

    {
        this->subDharma(accused->getDharma());
        return true;
    }
    else
    {
        return false;
    }
}

