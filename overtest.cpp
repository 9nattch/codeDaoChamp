#include <iostream>
#include <vector>
#include <cstdlib>
#include <limits>
#include <fstream>
#include <ctime>
#include <cmath>
#include <string>
#include <iomanip>
#include <algorithm>
#include "player.h"
#include "graph.h"
#include "console.h"

using namespace std;

void displayTextArt() {
    cout << "\n\n";
    cout << "*****************************************\n";
    cout << "*                                       *\n";
    cout << "*    WELCOME TO THE TRADE RUSH GAME     *\n";
    cout << "*                                       *\n";
    cout << "*****************************************\n";
    cout << "\n\n";
}

void displayStatus(const vector<Player>& players, int stockPrice) {
    SetConsoleColor(5);
    cout << "\n--- Current Status ---\n";
    cout << "Stock Price: " << stockPrice << " Baht\n";
    
    vector<string> names;
    vector<int> cash, shares, profit_loss;

    for (const auto& player : players){
        names.push_back(player.name);
        cash.push_back(player.cash);
        shares.push_back(player.shares);
        profit_loss.push_back(player.profit_loss);
    }

    DrawPlayerStatusBoxes(names, cash, shares, profit_loss);
    SetConsoleColor(7);

}

int calculateStockPrice(int newsLine) { //สุ่มข่าว
    if (newsLine >= 1 && newsLine <= 21) return rand() % (1300 - 850 + 1) + 850;
    if (newsLine >= 22 && newsLine <= 48) return rand() % (850 - 650 + 1) + 650;
    if (newsLine >= 49 && newsLine <= 85) return rand() % (600 - 400 + 1) + 400;
    if (newsLine >= 86 && newsLine <= 109) return rand() % (400 - 300 + 1) + 300;
    if (newsLine >= 110 && newsLine <= 131) return rand() % (300 - 200 + 1) + 200;
    return 0; // เผื่อกรณีไม่ตรงกับช่วงที่กำหนด
}

pair<int, string> generateMarketNews() {
    vector<pair<int, string>> newsList;
    ifstream file("news.txt");
    string line;
    int lineNumber = 0;
    
    if (!file) {
        cerr << "Error: Cannot open news_2.txt!\n";
        return {-1, "No news available."};
    }
    
    while (getline(file, line)) {
        lineNumber++;
        if (!line.empty()) {
            newsList.push_back({lineNumber, line});
        }
    }
    file.close();
    
    if (newsList.empty()) return {-1, "No news available."};
    
    int randomIndex = rand() % newsList.size();
    return newsList[randomIndex];
}

// ฟังก์ชันสร้างกรอบ *
void printWithBorder(const string& title, const pair<int, string>& currentNews, int round) {
    int maxLength = max(title.length(), currentNews.second.length()); // คำนวณความกว้างของกรอบ
    int totalWidth = maxLength + 4; // ขยายขนาดกรอบ (+6 เพื่อเว้นขอบ)
    
    // สร้างกรอบ *
    string border(totalWidth, '*');

    // สร้างข้อความ "ROUND X" ให้อยู่ตรงกลาง
    string roundText = " ROUND " + to_string(round) + " ";
    int roundPos = (totalWidth - roundText.length()) / 2; // หาตำแหน่งตรงกลาง
    string roundLine = string(roundPos, '*') + roundText + string(totalWidth - roundPos - roundText.length(), '*');

    // แสดงกรอบบน (มี "ROUND X")
    cout << "\n\n" << roundLine << endl;

    cout << "* " << setw(maxLength) << left << title << " *" << endl; // แสดงหัวข้อข่าว
    cout << "* " << string(maxLength, '-') << " *" << endl;// เส้นคั่นระหว่างหัวข้อกับข่าว
    cout << "* " << setw(maxLength) << left << currentNews.second << " *" << endl; // แสดงข่าว (เนื้อข่าวที่มีหมายเลขบรรทัด)
    cout << border << endl;// แสดงกรอบล่าง
}

void playerTurn(Player& player, int& stockPrice) {
    string input;
    int choice = 0;

    while (true) {
        cout << "\n" << player.name << ", what would you like to do?\n";
        SetConsoleColor(2); cout << "[1] Buy Shares\n";
        SetConsoleColor(4); cout << "[2] Sell Shares\n";
        SetConsoleColor(13); cout << "[3] Skip Turn\n";
        SetConsoleColor(7); cout << "Choice: ";
        SetConsoleColor(6);

        getline(cin, input); // อ่านอินพุตทั้งหมด

        // ✅ ตรวจสอบว่า input เป็นตัวเลข และไม่มีช่องว่าง
        if (input.length() == 1 && isdigit(input[0])) {
            choice = input[0] - '0'; // แปลง char เป็น int

            if (choice >= 1 && choice <= 3) {
                break; // ถ้าเลือกถูกต้อง ให้ออกจาก loop
            }
        }

        SetConsoleColor(4);
        cout << "Invalid choice! Please enter 1, 2, or 3.\n";
        SetConsoleColor(7);
    }

    if (choice == 1) {  // ซื้อหุ้น
        while (true) {
            SetConsoleColor(7);
            cout << "How many shares would you like to buy? (Stock price: " << stockPrice << "): ";
            cout << "[Enter 0 to go back]\n";
            SetConsoleColor(2);
            cout << "You want to buy : ";

            getline(cin, input);

            // ตรวจสอบว่าเป็นตัวเลขจำนวนเต็มบวก
            bool isValid = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid || input.empty()) {
                SetConsoleColor(4);
                cout << "Invalid input! Please enter an integer number.\n";
                SetConsoleColor(7);
                continue;
            }

            int amount = stoi(input); // แปลงเป็น int

            if (amount == 0) {
                SetConsoleColor(2);
                cout << "Returning to main menu...\n";
                SetConsoleColor(7);
                return playerTurn(player, stockPrice);
            }

            if (amount < 0) {
                SetConsoleColor(4);
                cout << "Invalid amount! Enter a positive number.\n";
                SetConsoleColor(7);
                continue;
            }

            int cost = amount * stockPrice;
            if (cost > player.cash) {
                SetConsoleColor(4);
                cout << "Not enough cash! You only have " << player.cash << " Baht.\n";
                SetConsoleColor(7);
            } else {
                player.cash -= cost;
                player.shares += amount;
                player.trades.push_back(-cost);
                break;
            }
        }
    } 
    else if (choice == 2) {  // ขายหุ้น
        while (true) {
            SetConsoleColor(7);
            cout << "How many shares would you like to sell? (Stock price: " << stockPrice << "): ";
            cout << "[Enter 0 to go back]\n";
            SetConsoleColor(4);
            cout << "You want to sell : ";

            getline(cin, input);

            // ตรวจสอบว่าเป็นตัวเลขจำนวนเต็มบวก
            bool isValid = true;
            for (char c : input) {
                if (!isdigit(c)) {
                    isValid = false;
                    break;
                }
            }

            if (!isValid || input.empty()) {
                SetConsoleColor(4);
                cout << "Invalid input! Please enter an integer number.\n";
                SetConsoleColor(7);
                continue;
            }

            int amount = stoi(input); // แปลงเป็น int

            if (amount == 0) {
                SetConsoleColor(2);
                cout << "Returning to main menu...\n";
                SetConsoleColor(7);
                return playerTurn(player, stockPrice);
            }

            if (amount < 0) {
                SetConsoleColor(4);
                cout << "Invalid amount! Enter a positive number.\n";
                SetConsoleColor(7);
                continue;
            }

            if (amount > player.shares) {
                SetConsoleColor(4);
                cout << "Not enough shares! You only have " << player.shares << " shares.\n";
                SetConsoleColor(7);
            } else {
                int revenue = amount * stockPrice;
                player.cash += revenue;
                player.shares -= amount;
                player.trades.push_back(revenue);
                break;
            }
        }
    }  
    else if (choice == 3) {  // ข้ามเทิร์น
        SetConsoleColor(2);
        cout << "Skipping turn...\n";
        SetConsoleColor(7);
    }
}

void sellAllShares(Player& player, int stockPrice) {// ขายทั้งหมดหลังจบเกม
    if (player.shares > 0) {
        int revenue = player.shares * stockPrice;
        player.cash += revenue;
        player.shares = 0;
        player.trades.push_back(revenue);
        cout << player.name << " sells all shares for " << revenue << " Baht.\n";
    }
}


int main() {
    SetConsoleShow("My Console App");  // ตั้งชื่อ console
    srand(time(0));  // ใช้เวลาในการสุ่มเลข

    int round = 1;  // ประกาศตัวแปร round และกำหนดค่าเริ่มต้น

    displayTextArt();

    int numPlayers;
    while (true) {
        cout << "Number of players (3-5): ";
        if(cin >> numPlayers && numPlayers >= 3 && numPlayers <= 5) {
            if (cin.peek() == '\n'){
                break;
            }   
        }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        SetConsoleColor(4);
        cout << "Invalid input! Please enter a number 3-5\n";
        SetConsoleColor(7);
    }
    
    cout << "You entered a valid number of players: " << numPlayers << endl;
    
    vector<Player> players = initializePlayers(numPlayers);

    pair<int, string> news = generateMarketNews();
    string title = "Market News"; // ตัวอย่างหัวข้อ

    SetConsoleColor(9);  // สีฟ้า
    cout << "\n=== Randomizing Starting Money ===\n";
    SetConsoleColor(7);
    randMoney(players);

    int stockPrice = 500;
    int rounds = 5;
    int graph[WIDTH], history[HISTORY_SIZE];
    loadHistory(history, graph);

    pair<int, string> currentNews;  // เก็บข่าวจากรอบก่อนหน้า

    for (round = 1; round <= rounds; ++round) {

        if (round > 1) {
            // ใช้ข่าวที่สุ่มในรอบก่อนหน้าในการคำนวณราคาหุ้นในรอบนี้
            stockPrice = calculateStockPrice(currentNews.first);
        }

        // สุ่มข่าวใหม่ในรอบนี้
        currentNews = generateMarketNews();  
        printWithBorder(title, currentNews, round);// เรียกใช้ฟังก์ชันสร้างกรอบ
        
        // เรียกใช้ฟังก์ชัน generateGraph เพื่อสร้างกราฟที่สัมพันธ์กับข่าว
        generateGraph(graph, currentNews.first);  // ส่ง newsLine ของข่าวที่สุ่ม
        displayGraph(graph);  // แสดงกราฟ

        displayStatus(players, stockPrice);

        // ให้ผู้เล่นเล่นในรอบนี้
        for (auto& player : players) {
            playerTurn(player, stockPrice);
            displayStatus(players, stockPrice);
        }

        // คำนวณกำไร/ขาดทุนของผู้เล่น
        for (auto& player : players) {
            int totalValue = player.shares * stockPrice;
            player.profit_loss = totalValue + player.cash - 50000;
        }
    }

    // ขายหุ้นทั้งหมดหลังเกมจบ
    cout << "\n\n";
    SetConsoleColor(11);
    cout << "--------------------------------";
    cout << "\n=== Final Selling Phase ===\n";
    cout << "--------------------------------";
    cout << "\n";
    for (auto& player : players) {
        cout << endl;
        sellAllShares(player, stockPrice);
    }
    
    saveHistory(graph);
    cout << endl;
    SetConsoleColor(4);
    cout << "********************************\n";
    cout << "*                              *\n";
    cout << "*";
    SetConsoleColor(14);
    cout << "          GAME OVER!          ";
    SetConsoleColor(4);
    cout << "*\n";
    cout << "*                              *\n";
    cout << "********************************\n";
    SetConsoleColor(7);
    cout << endl;

    // สรุปผลการแข่งขัน
    displayStatus(players, stockPrice);
    displayVictory(players);
    rankPlayers(players);
    ShowTitlePlayerder(players);  // แสดงฉายาผู้ชนะ

    return 0;
}