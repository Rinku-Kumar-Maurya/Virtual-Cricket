#include "game.h"

game::game()
{
    playerPerTeam = 4;
    maxBalls = 6;
    totalPlayers = 11;

    players[0] = "Virat ";
    players[1] = "Rohit ";
    players[2] = "Dhawan";
    players[3] = "Pant  ";
    players[4] = "Karthik";
    players[5] = "KLRahul";
    players[6] = "Jadeja";
    players[7] = "Hardik";
    players[8] = "Bumrah";
    players[9] = "BKumar";
    players[10] = "Ishant";

    isFirstInnings = false;
    teamA.name = "Team-A";
    teamB.name = "Team-B";
}

void game::welcomeMessage(){

    cout<<"----------------------------------------------------"<<std::endl;
    cout<<"****************************************************"<<std::endl;
    cout<<"*********** Welcome to Virtual Cricket *************"<<std::endl;
    cout<<"****************************************************"<<std::endl;
    cout<<"----------------------------------------------------"<<std::endl<<std::endl;

    cout<<"----------------------------------------------------"<<std::endl;
    cout<<">>>>>>>>>>>>>>>>>>> Instructions <<<<<<<<<<<<<<<<<<<"<<std::endl;
    cout<<"____________________________________________________"<<std::endl;
    cout<<"  1. Create 2 teams (Team-A and Team-B with 4"<<std::endl;
    cout<<"     player each) from a given pool of 11 players."<<std::endl;
    cout<<"  2. Lead the toss and decide the choice of play."<<std::endl;
    cout<<"  3. Each innings will be of 6 balls."<<std::endl;
    cout<<"----------------------------------------------------"<<std::endl<<std::endl;

}

void game::showAllPlayers(){
    cout<<endl;
    cout<<"-----------------------------------------------------"<<endl;
    cout<<">>>>>>>>>>>>>>>>>> Pool of Players <<<<<<<<<<<<<<<<<<"<<endl;
    cout<<"-----------------------------------------------------"<<endl;

    for(int i = 0; i< totalPlayers; i++){
        cout<<"\t\t"<<i<<". "<< players[i]<<endl;
    }

}

int game::takeIntegerInput(){
    int n;

    while(!(cin>> n)){
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(),'\n');
        cout<<"Invalid input! Please try again with valid input: "<<endl;
    }
    return n;
}

bool game::validateSelectedPlayers(int index){

    int n;
    vector<player> players;

    players = teamA.players;
    n = players.size();
    for (int i=0; i<n; i++){
        if(players[i].id == index){
            return false;
        }
    }
    return true;
}

void game::selectPlayers(){
    cout<<endl;
    cout<<"----------------------------------------------------"<<endl;
    cout<<">>>>>>>>>>>>> Create Team-A and Team-B <<<<<<<<<<<<<"<<endl;
    cout<<"----------------------------------------------------"<<endl;

    for(int i=0; i<playerPerTeam; i++){

        teamASelection:

            cout<<endl<<"Select player "<< i+1 <<" of Team A - ";
            int playerIndexTeamA = takeIntegerInput();

            if (playerIndexTeamA < 0 || playerIndexTeamA > 10){
                cout<<endl<<"Player with this id does not exist"<<endl;
                goto teamASelection;
            }else if(!validateSelectedPlayers(playerIndexTeamA)){
                cout<<endl<<"Player has already been selected"<<endl;
                goto teamASelection;
            }else{
                player teamAPlayer;
                teamAPlayer.id = playerIndexTeamA;
                teamAPlayer.name = players[playerIndexTeamA];
                teamA.players.push_back(teamAPlayer);
            }

       teamBSelection:

            cout<<endl<<"Select player "<< i+1 <<" of Team B - ";
            int playerIndexTeamB = takeIntegerInput();

            if(playerIndexTeamB < 0 || playerIndexTeamB > 10){
                cout<<endl<<"Player with this id does not exist"<<endl;
                goto teamBSelection;
            }else if(!validateSelectedPlayers(playerIndexTeamB)){
                cout<<"Player has already been selected"<<endl;
                goto teamBSelection;
            }else{
                player teamBPlayer;
                teamBPlayer.id = playerIndexTeamB;
                teamBPlayer.name = players[playerIndexTeamB];
                teamB.players.push_back(teamBPlayer);
            }

    }
}

void game::showTeamPlayers(){
    vector<player> teamAPlayers = teamA.players;
    vector<player> teamBPlayers = teamB.players;

    cout<<endl<<endl;
    cout<<"-----------------------\t\t-------------------------"<<endl;
    cout<<"<<<<<<<< Team A >>>>>>>\t\t<<<<<<<<< Team B >>>>>>>>"<<endl;
    cout<<"-----------------------\t\t-------------------------"<<endl;

    for (int i=0; i< playerPerTeam; i++){
        cout<<"\t"<<i<<"."<<teamAPlayers[i].name;
        cout<<"\t\t";
        cout<<"\t"<<i<<"."<<teamBPlayers[i].name<<endl;
    }
    cout<<"-----------------------\t\t-------------------------"<<endl<<endl;
}

void game::toss(){
    cout<<"----------------------------------------------------"<<endl;
    cout<<"<<<<<<<<<<<<<<<<<< Toss the coin >>>>>>>>>>>>>>>>>>>"<<endl;
    cout<<"----------------------------------------------------"<<endl<<endl;
    cout<<"Tossing the coin......"<<endl<<endl;
    cout<<"Press enter to see the results"<<endl;
    cin.ignore();

    srand(time(NULL));
    int tossResult = rand() % 2;
    if(tossResult == 0){
        cout<<"Team A won the toss"<<endl<<endl;
        tossChoice(teamA);
    }else{
        cout<<"Team B won the toss"<<endl<<endl;
        tossChoice(teamB);
    }

}

void game::tossChoice(team tossWinnerTeam){

    cout<<"Press enter key to continue"<<endl;
    cin.ignore();
    cout<<"Enter 1 to bat or 2 to bowl first."<<endl<<"1. Bat "<<endl<<"2. Bowl ";
    int tossInput = takeIntegerInput();
    cin.ignore(numeric_limits<streamsize>::max(),'\n');

    switch(tossInput){
        case 1:
            cout<<endl<<tossWinnerTeam.name<<" won the toss and elected to bat first"<<endl<<endl;

            if(tossWinnerTeam.name.compare("Team-A") == 0){
                battingTeam = &teamA;
                bowlingTeam = &teamB;
            }else{
                battingTeam = &teamB;
                bowlingTeam = &teamA;
            }
            break;

        case 2:
            cout<<endl<<tossWinnerTeam.name<<" won the toss and choose to bowl first"<<endl<<endl;

            if(tossWinnerTeam.name.compare("Team-A") == 0){
                battingTeam = &teamB;
                bowlingTeam = &teamA;
            }else{
                battingTeam = &teamA;
                bowlingTeam = &teamB;
            }
            break;

        default:
            cout<<endl<<"Invalid input. Please try again:"<<endl<<endl;
            tossChoice(tossWinnerTeam);
            break;
    }

}

void game::startFirstInnings(){
    cout<<"\t\t <<<<<<<<< FIRST INNINGS STARTS >>>>>>>>"<<endl<<endl;
    isFirstInnings = true;
    initializePlayers();
    playInnings();
}

void game::initializePlayers(){

    batsman = &battingTeam->players[0];
    bowler = &bowlingTeam->players[0];

    cout<<battingTeam->name<<" - "<<batsman->name<<" is batting "<<endl;
    cout<<bowlingTeam->name<<" - "<<bowler->name<<" is bowling "<<endl<<endl;

}

void game::playInnings(){

    for(int i=0; i<6; i++){
        cout<<"Please enter to bowl......";
        cin.ignore();
        cout<<"Bowling..."<<endl;
        bat();
        if(!validateInningsScore()){
            break;
        }
    }

}

void game::bat(){

    srand(time(NULL));
    int runsScored = rand() % 7;

    batsman->runsScored = batsman->runsScored + runsScored;
    battingTeam->totalRunsScored = battingTeam->totalRunsScored + runsScored;
    batsman->ballsPlayed = batsman->ballsPlayed + 1;

    bowler->ballsBowled = bowler->ballsBowled +1;
    bowlingTeam->totalBallsBowled = bowlingTeam->totalBallsBowled + 1;
    bowler->runsGiven = bowler->runsGiven + runsScored;

    if(runsScored != 0){
        cout<<endl<<bowler->name<<" to "<<batsman->name<<" "<<runsScored<<" runs!!"<<endl<<endl;
        showGameScorecard();
    }else{
        cout<<endl<<bowler->name<<" to "<<batsman->name<<" OUT!"<<endl<<endl;

        battingTeam->wicketsLost = battingTeam->wicketsLost + 1;
        bowler->wicketsTaken = bowler->wicketsTaken + 1;

        showGameScorecard();

        int nextPlayerIndex = battingTeam->wicketsLost;
        batsman = &battingTeam->players[nextPlayerIndex];
    }

}


bool game::validateInningsScore(){
    if(isFirstInnings){
        if(battingTeam->wicketsLost == playerPerTeam || bowlingTeam->totalBallsBowled == maxBalls){
            cout<<"\t\t <<<<<<<<<<< FIRST INNING ENDS >>>>>>>>>> "<<endl<<endl;
            cout<<battingTeam->name <<" "<<battingTeam->totalRunsScored<<" - "<<battingTeam->wicketsLost;
            cout<<" ("<<bowlingTeam->totalBallsBowled<<")"<<endl;
            cout<<bowlingTeam->name<<" needs "<<battingTeam->totalRunsScored + 1 <<" to win the game"<<endl;
            return false;
        }
    }else{
        if(battingTeam->totalRunsScored > bowlingTeam->totalRunsScored){
            cout<<"\t\t <<<<<<<<< SECOND INNING ENDS >>>>>>>>> "<<endl<<endl;

            choseWinner();
            return false;
        }
        else if(battingTeam->wicketsLost == playerPerTeam || bowlingTeam->totalBallsBowled == maxBalls){
            cout<<"\t\t <<<<<<<<< SECOND INNING ENDS >>>>>>>> "<<endl<<endl;

            choseWinner();
            return false;
        }
        else{
            return true;
        }
    }
    return true;
}

void game::showGameScorecard(){

    cout<<"----------------------------------------------------"<<endl;
    cout<<"  "<<battingTeam->name<<" "<<battingTeam->totalRunsScored<<" - "<<battingTeam->wicketsLost;
    cout<<"("<<bowler->ballsBowled<<") | "<<batsman->name<<" "<<batsman->runsScored<<"("<<batsman->ballsPlayed<<")\t";
    cout<<bowler->name<<" "<<bowler->ballsBowled<<" - "<<bowler->runsGiven<<" - "<<bowler->wicketsTaken<<endl;
    cout<<"----------------------------------------------------"<<endl<<endl;
}

void game::swap(team **r, team **s){
    team *pSwap = *r;
    *r = *s;
    *s = pSwap;
}

void game::startSecondInnings(){

    cout<<endl<<"\t\t <<<<<<<< SECOND INNINGS STARTS >>>>>>>>>"<<endl<<endl;
    isFirstInnings = false;
    swap(&battingTeam, &bowlingTeam);
    initializePlayers();
    playInnings();
}

void game::choseWinner(){
    if(battingTeam->totalRunsScored == bowlingTeam->totalRunsScored){
        cout<<endl<<"\t\t Match Ended in a Draw"<<endl<<endl;
    }else if(battingTeam->totalRunsScored > bowlingTeam->totalRunsScored){
        cout<<endl<<battingTeam->name<<" Won The Match"<<endl<<endl;
    }else{
        cout<<endl<<bowlingTeam->name<<" Won The Match"<<endl<<endl;
    }
    cout<<"\t\t <<<<<<<<<<<<< MATCH ENDS >>>>>>>>>>>>"<<endl;
}

void game::showGameSummary(team Team){

    cout<<battingTeam->name <<" "<<battingTeam->totalRunsScored<<" - "<<battingTeam->wicketsLost;
    cout<<" ("<<bowlingTeam->totalBallsBowled<<")"<<endl;
    cout<<"---------------------------------------------------"<<endl;
    cout<<"   PLAYERS\t\tBATTING\t\tBOWLING "<<endl;
    for(int i=0; i<playerPerTeam; i++){
        cout<<"---------------------------------------------------"<<endl;
        cout<<" "<<i<<". "<< Team.players[i].name;
        cout<<"\t\t"<<Team.players[i].runsScored<<"("<<Team.players[i].ballsPlayed<<")";
        cout<<"\t\t"<<Team.players[i].ballsBowled<<"-"<<Team.players[i].runsGiven<<"-"<<Team.players[i].wicketsTaken<<endl;
    }
    cout<<"---------------------------------------------------"<<endl;
}
