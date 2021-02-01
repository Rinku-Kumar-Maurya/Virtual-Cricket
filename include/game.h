#ifndef GAME_H
#define GAME_H
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<limits>
#include "team.h"


class game
{
    public:
        game();
        int playerPerTeam;
        int maxBalls;
        int totalPlayers;
        std::string players[11];

        bool isFirstInnings;
        team teamA, teamB;
        team *battingTeam, *bowlingTeam;
        player *batsman, *bowler;


        void welcomeMessage();
        void showAllPlayers();
        int takeIntegerInput();
        void selectPlayers();
        bool validateSelectedPlayers(int);
        void showTeamPlayers();
        void toss();
        void tossChoice(team);
        void startFirstInnings();
        void initializePlayers();
        void playInnings();
        void bat();
        bool validateInningsScore();
        void showGameScorecard();
        void swap(team **, team **);
        void startSecondInnings();
        void choseWinner();
        void showGameSummary(team);

};




#endif // GAME_H
