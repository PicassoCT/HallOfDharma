#ifndef PLAYER_H
#define PLAYER_H

#include <list>
#include <string>
#include "King.h"
class King;

class Player
{
public:
    /** Default constructor */
    Player() {};
    Player(std::string name, King* king);
    /** Default destructor */
    virtual ~Player();

    Player* getPlayer()
    {
        return this;
    }

    /** Set m_dharma
     * \param val New value to set
     */
    void addDharma(int val)
    {
        m_dharma += val;
    }
    void removeDharma(int val)
    {
        m_dharma -= val;
    }

    /** get the dharma of all this players and his lehnsmannList
    */
    int getTotalDharma();

    /** get the dharma of this player standalone
     */
    int getDharma()
    {
        return m_dharma;
    }

    /** Get Recruited by another Thane*/
    void acceptThane(Player* Thane)
    {
        thane = Thane;
    }

    /** Switch allegiance to another thane or no thane at all*/
    void removeThane(Player* ReplacementThane)
    {
        thane = ReplacementThane;
    }

    /** A Player can recruit other Lehnsmann- if his kharma is lower*/
    void recruitLehnsmann(Player * lehnsmann) {
        Recruits.push_back(lehnsmann);
        //king->registerPlayer(lehnsmann);

    };

    /** A Player can discard any direct lower Lehnsmann and his Followers*/
    void disownLehnsmann(Player * lehnsmann, Player *newThane);

    bool bailForPlayer(Player* accused)
    {
        bool oneOfMine= false;
            for (Player* trusted :  Recruits)
            {
                if (trusted == accused)
                {
                   oneOfMine = true; break;
                 }
            }

        if (oneOfMine   && abs(accused->getDharma()) < getDharma())

        {
            removeDharma(accused->getDharma());
            return true;
        }
        else
        {
            return false;
        }

    }

    std::list<Player*> lehnsmannList; //! List of followers of this Players

    std::string name;
    bool permaBanned = false;
    int  bannedForSeconds = 0;
protected:

private:
    std::list <Player*> Recruits;
    King* king;    //! Server and Central Hub of the system
    Player* thane; //! Mentor and Leader of this player
    int m_dharma; //! Kharma of this player
    float m_exp; //! Experience of this player
};

#endif // PLAYER_H
