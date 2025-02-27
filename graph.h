#ifndef GRAPH_H
#define GRAPH_H

const int WIDTH = 50;
const int HEIGHT = 10;
const int HISTORY_SIZE = 10;

void loadHistory(int history[], int graph[]);
void saveHistory(int graph[]);
void generateGraph(int graph[], int currentNews);
void displayGraph(int graph[]);


#endif
