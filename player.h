#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Player {
    string name;
    double cash;
    int shares;
    double profit_loss;
    double startingMoney;
    vector<double> trades;
};


vector<Player> initializePlayers(int numPlayers); // Function to create players
void randMoney(vector<Player>& players); // Function to randomize money
void displayVictory(const vector<Player> &players);
void rankPlayers(vector<Player>&players);
string getTitle(const Player& player); // Function to get player's title


#endif
