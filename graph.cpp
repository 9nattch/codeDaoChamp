#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include "graph.h"
#include <windows.h>
#include "console.h"


using namespace std;

void loadHistory(int history[], int graph[]) {
    ifstream inFile("graph_history.txt");
    if (inFile) {
        for (int i = 0; i < HISTORY_SIZE; i++) {
            inFile >> history[i];
            graph[i] = history[i];
        }
        inFile.close();
    } else {
        for (int i = 0; i < HISTORY_SIZE; i++) {
            graph[i] = HEIGHT / 2;
        }
    }
}

void saveHistory(int graph[]) {
    ofstream outFile("graph_history.txt");
    for (int i = WIDTH - HISTORY_SIZE; i < WIDTH; i++) {
        outFile << graph[i] << " ";
    }
    outFile.close();
}

void displayGraph(int graph[]) {
    SetGraphColor();
    for (int h = 0; h < HEIGHT; h++) {
        for (int w = 0; w < WIDTH; w++) {
            cout << (graph[w] == h ? "|" : " ");
        }
        cout << endl;
    }
    SetConsoleColor(7);
}

void generateGraph(int graph[], int newsLine) {
    // กำหนดค่าเริ่มต้นเพื่อป้องกันข้อผิดพลาด
    int baseChange = 0;

    // ข่าวดี → กราฟขาขึ้น
    if (newsLine >= 1 && newsLine <= 48) {
        baseChange = 1;
    }
    // ข่าวปกติ → กราฟกลาง ๆ
    else if (newsLine >= 49 && newsLine <= 85) {
        baseChange = 0;
        if (HISTORY_SIZE > 0) {
            graph[HISTORY_SIZE - 1] = HEIGHT / 2; // ป้องกัน index ผิดพลาด
        }
    }
    // ข่าวร้าย → กราฟขาลง
    else if (newsLine >= 86 && newsLine <= 131) {
        baseChange = -1;
    }

    // กำหนดค่าเริ่มต้นให้กราฟก่อนสุ่ม
    if (HISTORY_SIZE > 0) {
        graph[HISTORY_SIZE - 1] = graph[HISTORY_SIZE - 1];
    } else {
        graph[HISTORY_SIZE - 1] = HEIGHT / 2;
    }

    // สุ่มค่ากราฟตามแนวโน้มที่กำหนด
    for (int i = HISTORY_SIZE; i < WIDTH; i++) {
        int change = baseChange + (rand() % 2 - 1); // ปรับการผันผวนให้นุ่มนวล
        graph[i] = graph[i - 1] + change;

        // ปรับให้อยู่ในขอบเขต
        graph[i] = max(0, min(graph[i], HEIGHT - 1));
    }
}


