#ifndef MODERATOR_H
#define MODERATOR_H

#include <Player.h>


class Player;
class King;

class Moderator :  {
public:
    /** Default constructor */
    Moderator();
    Moderator(Player* player, King* king);

    /** Default destructor */
    virtual ~Moderator();

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

    void informLehnsmannOfReplacement(Moderator* newThane);

    bool getJudgmentOnPlayer(Player* accused);


protected:
    Player* player;
    King*   king;
private:
};

#endif // MODERATOR_H
