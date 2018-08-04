#include "Player.h"
#include "King.h"

Player::Player(std::string name, King* king)
{
    this->king = king;
    m_dharma = 0;
    name = name;
    //ctor
}

Player::~Player()
{
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

/** A Player can recruit other Lehnsmann- if his kharma is lower*/
void Player::recruitLehnsmann(Player * Lehnsmann)
{
    lehnsmannList.push_back(Lehnsmann);
};

/** A Player can discard any direct lower Lehnsmann and his Followers
    either adding him to another Thane - or setting him free
    Returns: null on move - otherwise a pointer to the player set free
    */
void Player::disownLehnsmann(Player * lehnsmann, Player *newThane)
{
    lehnsmannList.remove(lehnsmann);
    if (newThane == nullptr)
    {
        king->setFree(lehnsmann);
        return;
    }
    else
    {
        newThane->recruitLehnsmann(lehnsmann);
        return;
    }


};

