#include "player.h"
#include <iostream>
#include <ctime>
#include <algorithm>
#include <sstream>
#include "console.h"  
using namespace std;

vector<Player> initializePlayers(int numPlayers) {
    vector<Player> players;
    int startMoney = 50000;  

    cin.ignore();

    for (int i = 0; i < numPlayers; i++) {
        Player p;  
        cout << "Enter name for player " << i + 1 << ": ";
        getline(cin, p.name);
        p.cash = startMoney;
        p.shares = 0;
        p.profit_loss = 0;
        players.push_back(p);
    }

    return players;
}

void randMoney(vector<Player>& players) {
    int amounts[] = {1000, 2000, -1000, -2000, 5000, 3000, 4000, -2000, 4600, -3000, 5600, 4000, -3440, 1000};
    int numAmounts = sizeof(amounts) / sizeof(amounts[0]);

    srand(time(0));

    for (size_t i = 0; i < players.size(); i++) {
        int randomMoney = amounts[rand() % numAmounts];
        players[i].cash += randomMoney;
        
        SetConsoleColor(5);
        cout << players[i].name ;

        SetConsoleColor(7);
        cout << " gets: " ;

        SetConsoleColor(4);
        cout << randomMoney ;
        
        SetConsoleColor(7);
        cout << " baht";

        SetConsoleColor(6);
        cout << " | ";
        
        SetConsoleColor(7);
        cout << "Remaining money : " ;
        
        SetConsoleColor(10);
        cout << players[i].cash ;
        
        SetConsoleColor(7);
        cout << " baht\n";
    }

}
//ฉายา
string getTitle(const Player& player) {

    int highRiskTrades = 0, lowRiskTrades = 0, lossTrades = 0;
    int totalTrades = player.trades.size();
    double maxLoss = 0, totalProfit = player.cash + (player.shares * 500) - player.startingMoney;
    double cashRatio = player.cash / player.startingMoney;

    for (double trade : player.trades) {
        if (trade >= 5000) highRiskTrades++;
        if (trade < 4000) lowRiskTrades++;
        if (trade < 0) {
            lossTrades++;
            if (-trade > maxLoss) maxLoss = -trade;
        }
    }

    if (player.cash > 80000) return "Overnight millionaire";
    if (totalProfit > player.startingMoney + 10000) return "The Deal Maker";
    if (highRiskTrades > totalTrades / 2) return "The Risk Maverick";
    if (lowRiskTrades == totalTrades) return "The Safety Guru";
    if (cashRatio >= 0.7) return "The Money Hoarder";
    if (lossTrades > 0 && player.cash > player.startingMoney) return "The Steady Investor";
    if (player.cash < 15000) return "The Downfall King/Queen";
    if (maxLoss >= player.startingMoney * 0.5) return "The One Shot Wonder";
    if (lossTrades > totalTrades / 2) return "The Jinxed Emperor";

    return "The Daily Trader";
}
//-----------
 

//ประกาศผู้ชนะ
void displayVictory(const vector<Player> &players){
    if( players.empty()) {

        cout << "No players available.\n";
        return;
    } 
    auto winner = max_element(players.begin(), players.end(), [](const Player &a, const Player &b){
        return a.cash < b.cash;
    });
    DrawWinnerBanner(winner -> name, winner -> cash);
}
//--------------


//ลำดับเเรงค์
void rankPlayers(vector<Player> &players){
    sort(players.begin(), players.end(), [](const Player &a, const Player &b){
        return a.cash > b.cash;
    });

    if (players.empty()) {
        cout << "No players available!\n";
        return;
    }
    SetConsoleColor(5);
    cout << endl;
    cout <<   "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+";
    cout << "\n|    === Player Ranking ===    |\n";
    cout <<   "+~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~+";
    SetConsoleColor(14);
    cout << "\n**                            **\n";
    cout << "**                            **\n";
    SetConsoleColor(7);
     
     DrawrankPlayers(players);
}

//---------------------------
