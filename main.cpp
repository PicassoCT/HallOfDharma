#include <iostream>

#include "windows.h"
#include "king.h"
#include "Moderator.h"
#include "Player.h"
#include <time.h>

using namespace std;

//Here I will create an array of prefixes to help generate names.
// I am banking on multiplication to ensure a large number of names
// by using 7 prefixes and 20 stems, and 16 suffixes I should be able to
// create about 7 * 20 * 16 = 2240 names out of 312 bytes of data (In my earlier
// example from the forum I used this code to generate male and female names,
// but here I combined them).
char NamePrefix[][5] = {
	" ", //who said we need to add a prefix?
	"bel", //lets say that means "the good"
	"nar", //"The not so good as Bel"
	"xan", //"The evil"
	"bell", //"the good"
	"natr", //"the neutral/natral"
	"ev", //Man am I original
};

	char NameSuffix[][5] = {
	" ", "us", "ix", "ox", "ith",
	"ath", "um", "ator", "or", "axia",
	"imus", "ais", "itur", "orex", "o",
	"y"
};


const char NameStems[][10] = {
	"adur", "aes", "anim", "apoll", "imac",
	"educ", "equis", "extr", "guius", "hann",
	"equi", "amora", "hum", "iace", "ille",
	"inept", "iuv", "obe", "ocul", "orbis"
};


//The return type is void because we use a pointer to the array holding
// the characters of the name.
std::string NameGen()
{
	std::string PlayerName = std::string(""); //initialize the string to "" (zero length string).
	//add the prefix...
	PlayerName.append(NamePrefix[(rand() % 5)]);
	//add the stem...
	PlayerName.append(NameStems[(rand() % 19)]);
	//add the suffix...
	PlayerName.append(NameSuffix[(rand() % 15)]);
	//Make the first letter capital...

	return PlayerName;
}

int main()
{
    King king;
    std::list<Player*> allPlayers;
    srand (time(NULL));

    while (true)
    {
        king.audience(500);
        Sleep(500);
        // Simulates the whole Ecosystem

        //Random Create new inhabitants
        if (rand()%100 > 70)
            {


            Player* aNewGuy = new Player( NameGen(), &king);
            king.registerPlayer(aNewGuy);
            allPlayers.push_back(aNewGuy);
            std::cout<< "New Player enters system "<< aNewGuy->name <<std::endl;
            }

        //Random let them recruit one another
        if (rand()%100 > 50){
            int listIndex= rand() % allPlayers.size();
            int recruitIndex= rand() % allPlayers.size();

            for  (Player* one : allPlayers) {
                    listIndex--;
                if (!listIndex){
                      for  (Player* other : allPlayers) {
                        recruitIndex--;
                        if (!recruitIndex)
                            one->recruitLehnsmann(other);
                      }
                }
            }
        }

        //Random create Up and Downs in Kharma for players
        for  (Player* player : allPlayers) {
             if (rand()%100 > 50)
                    player->addDharma(abs(rand()) % 10);
             else
                    player->subDharma(abs(rand()) % 5);
        }

        //Make Players behave Rational
         for  (Player* one : allPlayers) {
                one->behaveRational();
            }


    }

    return 0;
}
