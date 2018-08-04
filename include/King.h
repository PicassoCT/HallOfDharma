#ifndef KING_H
#define KING_H

// Administrative Class - all Players are subject of the king
// All Moderators are subject of the king
// The King is able to ban Moderators.
// There is only one King, as there is only one Server
#include "Player.h"
#include "Moderator.h"

class Moderator;
class Player;

class King
{
public:
    /** Default constructor */
    King();
    /** Default destructor */
    virtual ~King();

    void banPlayerForTime(Player* playerToBan, int durationInSeconds)
    {
        playerToBan->removeDharma(playerToBan->getDharma);
        playerToBan->bannedForSeconds = durationInSeconds;
        Populus.remove(playerToBan);
        Brigands.push_back(playerToBan);
    };

    bool requestPermanentBan(Player* accused, Moderator* judicator, Player* bondsman)
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

    void setFree(Player* vogelfrei)
    {
        Populus.push_back(vogelfrei);
    };

    void serviceRoutine( int milliSecondsPast)
    {
        surveyBrigands(milliSecondsPast/1000);

        bandBrigands();

    };

    void surveyBrigands(int timePassedInSeconds)
    {
        for (Player* guilty :  Brigands)
        {
            guilty->bannedForSeconds -= timePassedInSeconds;
            if (guilty->bannedForSeconds >= 0)
            {
                //redeemed player
                Populus.push_back(guilty);
                Brigands.remove(guilty);
            }
        }
    }

    void banBrigands()
    {
        for (Player* subject :  Populus)
        {
            if (subject->getDharma() < 0)
            {
                banPlayerForTime(subject, abs(subject->getDharma()))
            }
        }
    }

    void moderatorInsteadOfTheModerator( Moderator * toBeReplaced, Player * replacement, Player* toBeReplacedPlayer, Moderator* replacementModerator)
    {
        Player* newPlayer = new Player(toBeReplaced->name,king);
        *newPlayer = *toBeReplaced.getPlayer();
        memccpy(toBeReplacedPlayer, newPlayer, sizeof(newPlayer));
        Populus.push_back(newPlayer);
        Aristocracy.remove(toBeReplaced);
        delete (*toBeReplaced);

        Moderator* newModerator = new Moderator(replacement,king);
        Aristocracy.push_back(newModerator);
        Populus.remove(replacement);
        delete(*replacement);

    };

    void registerPlayer(Player* player)
    {
        Populus.push_back(player);
    };

    void removePlayer(Player* player)
    {
        Populus.remove(player);
    };
protected:

private:
    List<Player*> Inferno;
    List<Player*> Brigands;
    List<Player*> Populus;
    List<Moderator*> Aristocracy;
};

#endif // KING_H
