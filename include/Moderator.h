#ifndef MODERATOR_H
#define MODERATOR_H

#include "Player.h"
#include "King.h"
//King of a Dharma Tree

class King;
class Player;

class Moderator : public Player
{
public:
    /** Default constructor */
    Moderator(Player* player, King* king);

    /** Default destructor */
    virtual ~Moderator()
    {
        delete (this->getPlayer());
    };

    /** Ban Player - Moderators can only ban players with lower dharma -
     all Lehnsmann of a banned Player a ban is removing recursive  */
    bool banLehnsmann(Player*, int durationInMinutes);

    /** Permanently (Lifetime) Banning a Player,
     needs for anyone in a hierarchy a second Judge (Judicator),
     optionally a bondsman (same hierarchy level) can step up
     This is not necessary for hierarchyless Players in dharma debt,
      and hierarchy bound players whos group is in debt (brigands).
    */
    bool requestPermaBan(Player* accused, Moderator* judicator, Player* bondsman) ;

    /** Check for Feudal Consistency */
    void checkForHierarchyConsistency(void);


    /**Exchange  Moderator role*/
    void moderatorInsteadOfTheModerator(Moderator *oldOne, Player * newOne, King* KingToReportTo);

    bool getJudgmentOnPlayer(Player* accused)
    {
        return accused->getTotalDharma() < this->getTotalDharma();
    } //TODO Get better judgment function
protected:
    Player* getModeratorPlayer()
    {
        return this->getPlayer();
    };
    King*   king;
private:
};

#endif // MODERATOR_H
