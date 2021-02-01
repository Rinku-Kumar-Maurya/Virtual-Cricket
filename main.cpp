#include "game.h"

void pause();

int main()
{
    game g;
    g.welcomeMessage();
    pause();
    g.showAllPlayers();
    pause();
    g.selectPlayers();
    pause();
    g.showTeamPlayers();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');
    pause();
    g.toss();
    pause();
    g.startFirstInnings();
    pause();
    g.startSecondInnings();
    pause();
    g.showGameSummary(g.teamA);
    pause();
    g.showGameSummary(g.teamB);


    return 0;
}

void pause(){
    cout<<endl<<"Press enter key to continue"<<endl;
    cin.ignore();
}
