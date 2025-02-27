#include <windows.h>
#include "console.h"
#include <iostream>
#include <iomanip>
#include <vector>

using namespace std;

void SetConsoleColor(int color){//เปลี่ยนสีconsole
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void SetPlayerNameColor(){
    SetConsoleColor(13);
}

void SetConsoleShow(const char* title){
    SetConsoleTitleA(title);
}

void SetStatusPlayerColor(){//เปลี่ยนสีสถานะผู้เล่น
    SetConsoleColor(11);
}

void SetGraphColor(){
    SetConsoleColor(10);
}



//กรอบสรุปยอดต่างๆของผู้เล่น
void DrawPlayerStatusBoxes(const vector<string> &names, const vector<int> &cash, const vector<int> &shares, const vector<int> &profit_loss) {
    int numPlayers = names.size();
    if (numPlayers > 5) numPlayers = 5;
    int valueWidth = 10;  // ความกว้างของค่าตัวเลข
    int labelWidth = 13;  // ความกว้างของข้อความ Cash, Shares, Profit/Loss
    int boxWidth = labelWidth + valueWidth + 3;  // กำหนดขนาดกล่อง
    string spaceBetween = "   "; // ระยะห่างระหว่างกล่อง

    // เส้นขอบบน
    for (int i = 0; i < numPlayers; i++) {
        cout << "+" << string(boxWidth, '-') << "+" << spaceBetween;
    }
    cout << endl;

    // ชื่อผู้เล่น
    for (int i = 0; i < numPlayers; i++) {
        SetConsoleColor (11);
        cout << "| " << left << setw(boxWidth - 2) << names[i] << "| " << spaceBetween;
    }
    cout << endl;

    // เส้นขอบกลาง
    for (int i = 0; i < numPlayers; i++) {
        cout << "+" << string(boxWidth, '-') << "+" << spaceBetween;
    }
    cout << endl;

    // แสดงเงินสด
    for (int i = 0; i < numPlayers; i++) {
        SetConsoleColor(2);
        cout << "| " << setw(labelWidth) << left << "Cash:" << setw(valueWidth) << right << cash[i] << " | " << spaceBetween;
    }
    cout << endl;

    // แสดงจำนวนหุ้น
    for (int i = 0; i < numPlayers; i++) {
        SetConsoleColor(6);
        cout << "| " << setw(labelWidth) << left << "Shares:" << setw(valueWidth) << right << shares[i] << " | " << spaceBetween;
    }
    cout << endl;

    // แสดงกำไร/ขาดทุน
    for (int i = 0; i < numPlayers; i++) {
        SetConsoleColor(12);
        cout << "| " << setw(labelWidth) << left << "Profit/Loss:" << setw(valueWidth) << right << profit_loss[i] << " | " << spaceBetween;
    }
    cout << endl;

    // เส้นขอบล่าง
    for (int i = 0; i < numPlayers; i++) {
        cout << "+" << string(boxWidth, '-') << "+" << spaceBetween;
    }
    cout << endl;

    SetConsoleColor(7); // รีเซ็ตสีให้กลับเป็นปกติ
}
//---------


//พิมพ์victory
void printVictory(){
    SetConsoleColor(10);
    string border = string(87, '*'); // กรอบดอกจัน
    string space  = string(85, ' '); // เว้นว่างด้านใน
        cout << endl;
        cout << "\n" << border << "\n";  
        cout << "*" << space << "*\n";

        SetConsoleColor(14);
        cout << "*   **      **   ********   *******   ********    ******     *******     **      **   *" << endl; 
        cout << "*   **      **      **     **            **      *      *    **      *    **    **    *" << endl; 
        cout << "*    **    **       **     **            **      *      *    ** *****       ****      *"  << endl;
        cout << "*     **  **        **     **            **      *      *    **    **        **       *"  << endl;
        cout << "*       **       ********   *******      **       ******     **     **       **       *" << endl;

        SetConsoleColor(10);
        cout << "*" << space << "*";
        cout << "\n" << border << "\n"; 
        SetConsoleColor(7);

    }


//วาดถ้วยรางวัล
void drawTrophy() {
    cout << endl;
    cout << "     ________    " << endl;
    cout << "   /         \\    " << endl;
    cout << "   |   *  *   |   " << endl;
    cout << "   |   ____   |   " << endl;
    cout << "   \\_________/    " << endl;
    cout << "        ||        " << endl;
    cout << "      __||__      " << endl;
    cout << "     |______|     " << endl;
    cout << "  __//      \\__   " << endl;
    cout << " //____________\\  " << endl;
    cout << " |______________|  " << endl;
    cout << endl;

}



//กรอบประกาศผู้ชนะ
void DrawWinnerBanner(const string &winnerName, int cash) {
    printVictory();//victory

    SetConsoleColor(14);
    drawTrophy();//วาดถ้วย

    SetConsoleColor(10); //สีเส้นกรอบเขียว
    string border = string(40, '*'); // กรอบดอกจัน
    string space  = string(38, ' '); // เว้นว่าง

    // พิมพ์กรอบ
    cout << "\n" << border << "\n";  
    cout << "*" << space << "*\n";

    // ยินดี
    SetConsoleColor(10); //แดง
    cout <<"*";
    SetConsoleColor(4);
    cout <<"           CONGRATULATIONS!!!";
    SetConsoleColor(10);
    cout <<"         *\n";

    SetConsoleColor(10); // สีกรอบเขียว  
    cout << "*" << space << "*\n";
    cout << border << "\n";

    // ข้อความชื่อผู้ชนะและเงินรางวัล
    SetConsoleColor(10);
    cout << "*" << space <<"*\n";
    cout << "*";
    SetConsoleColor(14);
    cout <<"       WINNER:  " << setw(14) << winnerName;
    SetConsoleColor(10);
    cout << "        *\n"; // 
    cout << "*";
    SetConsoleColor(14);
    cout <<"    CASH PRIZE:  " << setw(12) << cash << " Baht";
    SetConsoleColor(10);
    cout <<"    *\n"; // เพิ่มช่องว่าง
  
    SetConsoleColor(10); // สีกรอบ3
    cout << "*" << space << "*\n";
    cout << border << "\n";

    // ข้อความท้าย
    SetConsoleColor(10);//สี 
    cout << "*";
    SetConsoleColor(11);
    cout <<"          You are the Best!";
    SetConsoleColor(10);
    cout << "           *\n";
    cout << border << "\n\n";

    // รีเซ็ตสี
    SetConsoleColor(7); // สีเริ่มต้น
}


//----------------------


//วาดแรงค์ขั้นบันได
void DrawrankPlayers(vector<Player> &players) {
    int totalPlayers = players.size();

    if (totalPlayers == 0) {  
        cout << "Error: No players available." << endl;
        return;
    }

    int maxWidth = 35;  // กรอบอันดับ 5 กว้างสุด
    int minWidth = 15;  // กรอบอันดับ 1 บนยอดพีระมิด
    int widthStep = 5;  // ลดลงทีละ 5

    for (int i = 0; i < totalPlayers; i++) {
        int frameWidth = maxWidth + (i * widthStep);
        if (frameWidth < minWidth) frameWidth = minWidth;
    
        string playerInfo = "NO." + to_string(i + 1) + " " + players[i].name + 
                            " | Cash: " + to_string((int)players[i].cash) + " Baht";
    

        
        // ตรวจสอบว่ากรอบเล็กกว่าข้อความ
        int padding = max(0, frameWidth - (int)playerInfo.length() - 2);
    

        if (i == 0) SetConsoleColor(12);  
        else if (i == 1) SetConsoleColor(14);  
        else if (i == 2) SetConsoleColor(10);  
        else if (i == 3) SetConsoleColor(9);   
        else if (i == 4) SetConsoleColor(13);  

        cout << "+" << string(frameWidth, '-') << "+" << endl;
        cout << "| " << playerInfo << string(padding, ' ') << " |" << endl;
        cout << "+" << string(frameWidth, '-') << "+" << endl;

        SetConsoleColor(7);
    }
    
}
//-------------


//วาดกรอบฉายา
const string RESET = "\033[0m";
const string COLORS[] = {
    "\033[31m", // สีแดง
    "\033[32m", // สีเขียว
    "\033[33m", // สีเหลือง
    "\033[34m", // สีน้ำเงิน
    "\033[35m", // สีม่วง
    "\033[36m"  // สีฟ้า
};
void DrawTitleBanner(const string& text) {
    int length = text.length();
    string border(length + 4, '=');

    static int colorIndex = 0;
    string color = COLORS[colorIndex % 6];
    colorIndex++; // เปลี่ยนสีสำหรับกรอบถัดไป

    cout << color;
    cout << border << "\n";
    cout << "* " << text << " *\n";
    cout << border << "\n";
    cout << RESET;
}

// ฟังก์ชันแสดงผล
void ShowTitlePlayerder(const vector<Player>& players) {
    SetConsoleColor(11);
    cout << endl;
    cout << endl;
    cout << "\n*****************************\n";
    cout << "*   === Player Titles ===   *"   ;
    cout << "\n*****************************\n";
    SetConsoleColor(14);
    cout << "||\n";
    SetConsoleColor(7);
    for (const auto& player : players) {
        string text = player.name + " is \"" + getTitle(player) + "\""; // สร้างข้อความก่อนใช้
        DrawTitleBanner(text);
    }
}
