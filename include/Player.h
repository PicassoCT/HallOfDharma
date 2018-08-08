#ifndef PLAYER_H
#define PLAYER_H

#include <stdlib.h>
#include <list>
#include <string>

class King;
class Moderator;

class Player
{
public:
    /** Default constructor */
    Player() {};
    Player(std::string name, King* king);
    /** Default destructor */
    virtual ~Player();

    Player* getPlayer();

    /** Set m_dharma
     * \param val New value to set
     */
    void addDharma(int val);
    void subDharma(int val);

    /** get the dharma of all this players and his lehnsmannList
    */
    int getTotalDharma();

    /** get the dharma of this player standalone
     */
    int getDharma();

    /** Get Recruited by another Thane*/
    void swareToThane(Player* Thane);

    void swareToThane(Moderator* Thane);

    void informOfBetrayal(Player* formerLehnsmann, Player* newThane);

    /** A Player can recruit other Lehnsmann- if his kharma is lower*/
    void recruitLehnsmann(Player * lehnsmann) ;

    /** A Player can discard any direct lower Lehnsmann and his Followers*/
    void disownLehnsmann(Player * lehnsmann, Player* newThane);

    bool bailForPlayer(Player* accused);
    void behaveRational(); //DELME
    std::list<Player*> lehnsmannList; //! List of followers of this Players
    std::string name;
    bool permaBanned = false;
    int  bannedForSeconds = 0;
    int strikes = 0;
    Player* thane; //! Mentor and Leader of this player

protected:

private:
    std::list <Player*> Recruits;
    King* king;    //! Server and Central Hub of the system
    int m_dharma; //! Kharma of this player
    float m_exp; //! Experience of this player
};

#endif // PLAYER_H
