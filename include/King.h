#ifndef KING_H
#define KING_H

#include <fstream>
#include<list>

// Administrative Class - all Players are subject of the king
// All Moderators are subject of the king
// The King is able to ban Moderators.
// There is only one King, as there is only one Server



class Moderator;
class Player;
class Moderator;

class King
{
public:
    /** Default constructor */
    King();
    /** Default destructor */
    virtual ~King();



    void banPlayerForTime(Player* playerToBan, int durationInSeconds);

    bool requestPermanentBan(Player* accused, Moderator* judicator, Player* bondsman);

    void audience( int milliSecondsPast);


    void lowerToComoner(Moderator* nowComoner);

    void surveyBrigands(float timePassedInSeconds);

    void banBrigands();

    void riseAKnight(Player* newNoble);

    void moderatorInsteadOfTheModerator( Moderator * toBeReplaced, Player * replacement);

    void registerPlayer(Player* player);

    void removePlayer(Player* player);
    std::list<Moderator*> Aristocracy;
protected:

private:
    std::list<Player*> Inferno;
    std::list<Player*> Brigands;
    std::list<Player*> Populus;

};

#endif // KING_H
