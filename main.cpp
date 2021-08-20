#include <iostream>
#include <vector>

#include "PathFinder.h"

using namespace std;

void inputMaze(PathFinder&);
void inputStart(PathFinder&);
void inputDestination(PathFinder&);
void printCommands(PathFinder&, int);

int main() {

    system("clear");

    auto pf = PathFinder();


    int choice;
    while (true) {
        printCommands(pf, choice);
        cin >> choice;
        system("clear");
        switch (choice) {
            case 0:
                inputMaze(pf);
                system("clear");
            break;
            case 1:
                inputStart(pf);
                system("clear");
            break;
            case 2:
                inputDestination(pf);
                system("clear");
            break;
            case 3:
                system("clear");
                pf.printShortestPath();
            break;
            case 4:
                system("clear");
            break;
            default:
                return 0;
            break;
        }
    }

    return 0;
}

void inputStart(PathFinder &pf) {
    int r, c;
    cout << "\033[1;32mstart\033[0m: ";
    cin >> r >> c;
    pf.setStart(r, c);
}

void inputDestination(PathFinder &pf) {
    int r, c;
    cout << "\033[1;32mdestination\033[0m: ";
    cin >> r >> c;
    pf.setDestination(r, c);
}


void inputMaze(PathFinder &pf) {
    char val;
    int height, width;

    cout << "\033[1;32mheight\033[0m: ";
    cin >> height;
    cout << "\033[1;32mwidth\033[0m: ";
    cin >> width;

    system("clear");

    char arr[height][width];
    vector<vector<char>> maze;
    vector<char> row;

    for (int i = 0; i < height; ++i) {
        for (int j = 0; j < width; ++j) {
            cin >> val;
            row.push_back(val);
        }
        maze.push_back(row);
        row.clear();
    }
    pf.setMaze(maze);
}

void printCommands(PathFinder &pf, int choice) {
    if (choice != 3 && pf.hasMazeSet()) {
        pf.printMaze();
        cout << "\n\n";
    }
    cout << "\033[1;33m0\033[0m. input maze" << endl;
    cout << "\033[1;33m1\033[0m. input start" << endl;
    cout << "\033[1;33m2\033[0m. input destination" << endl;
    cout << "\033[1;33m3\033[0m. print path" << endl;
    cout << "\033[1;33m4\033[0m. print maze" << endl;
}

