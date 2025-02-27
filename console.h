#include<iostream>
#include <vector>
#include <string>
#include "player.h"

using namespace std;
#ifndef CONSOLE_H
#define CONSOLE_H

void SetConsoleColor(int color);// ตั้งสีคอนโซล
void SetConsoleShow(const char* title);//ตั้งชื่อคอนโซล
void SetStatusPlayerColor();// ตั้งสีstatusplayer
void SetGraphColor();//ตั้งสีกราฟ


void DrawPlayerStatusBoxes(const vector<string> &names, const vector<int> &cash, const vector<int> &shares, const vector<int> &profit_loss);
void DrawGraphBorder(); //วาดกรอบกราฟ
void printVictory(); // victory
void drawTrophy(); //วาดถ้วยรางวัล
void DrawWinnerBanner(const string &winnerName, int cash);//กรอบประกาศผู้ชนะ
void DrawrankPlayers(vector<Player> &players);//วาดกรอบเเรงค์
void DrawTitleBanner(const string & text);
void ShowTitlePlayerder(const vector<Player> & players);
#endif