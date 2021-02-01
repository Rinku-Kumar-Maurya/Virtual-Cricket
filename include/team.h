#ifndef TEAM_H
#define TEAM_H

#include<vector>
#include<player.h>

class team
{
    public:
        team();
        std::string name;
        int totalRunsScored;
        int wicketsLost;
        int totalBallsBowled;
        std::vector<player> players;


};

#endif // TEAM_H
