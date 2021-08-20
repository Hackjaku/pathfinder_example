#include "PathFinder.h"

using namespace std;

// ? CONTAINS
bool operator <= (vector<Vertex> vec, Vertex element) {
    for (const auto &value : vec) {
        if (value.coords == element.coords) {
            return true;
        }
    }
    return false;
}


PathFinder::PathFinder(vector<vector<char>> mazeVec) {
    this->maze = mazeVec;
}


void PathFinder::addVisited() {
    for (const auto adj : this->adjacent) {
        if (this->visited <= adj) {
            continue;
        } else {
            if (this->maze[adj.coords.first][adj.coords.second] == '.') {
                this->visited.push_back(adj);
            }
        }
    }
}

int PathFinder::getVisitedDistanceFromCoords(int x, int y) {
    for (auto &v : this->visited) {
        if (v.coords.first == x && v.coords.second == y) {
            return v.distance;
        }
    }
    return -1;
}

void PathFinder::printShortestPath() {
    if (this->maze.empty()) {
        cout << "\033[1;34mno maze found\033[0m\n\n";
        return;
    }
    this->visited.push_back(this->start);
    for (int i = 0; i < this->visited.size(); ++i) {
        this->addAdjacents(this->visited[i]);
        this->addVisited();
        this->adjacent.clear();
    }
    // Vertex destination = Vertex(this->maze.size() - 1, this->maze[0].size() - 1);
    // return (this->visitedV <= destination);
    vector<Vertex> shortestPath;
    if (this->visited <= this->destination) {
        int distance = 0;
        for (const auto &val : this->visited) {
            if (val.coords == this->destination.coords) {
                distance = val.distance - 1;
                shortestPath.push_back(val);
                break;
            }
        }

        auto dest = this->destination;

        while (distance >= 0) {
            auto adj = getAdjacents(dest);
            for (const auto &val : adj) {
                if (val.distance == distance) {
                    shortestPath.push_back(val);
                    dest = val;
                    --distance;
                    adj.clear();
                    break;
                }
            }
        }
    } else {
        cout << "\033[1;34munreachable\033[0m\n\n";
    }

    for (int i = 0; i < this->maze.size(); ++i) {
        for (int j = 0; j < this->maze[0].size(); ++j) {
            if (this->maze[i][j] == '.') {
                Vertex v = Vertex(i, j, 0);
                if (v.coords == this->destination.coords) {
                    cout << "\033[1;36mX\033[0m ";
                } else if (v.coords == this->start.coords) {
                    cout << "\033[1;33mO\033[0m ";
                } else if (shortestPath <= v) {
                    cout << "\033[1;32m.\033[0m ";
                } else {
                    cout << "\033[1;34m.\033[0m ";
                }
            } else {
                cout << "\033[1;31m+\033[0m ";
            }
        }
        cout << endl;
    }
    cout << endl << endl;
}

vector<Vertex> PathFinder::getAdjacents(Vertex v) {
    vector<Vertex> adj;
    for (auto &val : this->visited) {
        if (val.coords.first == v.coords.first) {
            if (val.coords.second == v.coords.second + 1 || val.coords.second == v.coords.second - 1) {
                adj.push_back(val);
                continue;
            }
        }
        if (val.coords.second == v.coords.second) {
            if (val.coords.first == v.coords.first + 1 || val.coords.first == v.coords.first - 1) {
                adj.push_back(val);
                continue;
            }
        }
        if (adj.size() == 4) {
            break;
        }
    }
    return adj;
}

Vertex::Vertex(int row, int col, int dist) {
    this->coords.first = row;
    this->coords.second = col;
    this->distance = dist;
}

Vertex::Vertex() {
    this->coords.first = 0;
    this->coords.second = 0;
    this->distance = 0;
}

void PathFinder::addAdjacents(Vertex v) {
    Vertex vt;
    if (v.coords.first != 0) {
        vt.coords.first = v.coords.first - 1;
        vt.coords.second = v.coords.second;
        vt.distance = v.distance + 1;
        this->adjacent.push_back(vt);
    }
    if (v.coords.second != 0) {
        vt.coords.first = v.coords.first;
        vt.coords.second = v.coords.second - 1;
        vt.distance = v.distance + 1;
        this->adjacent.push_back(vt);
    }
    if (v.coords.first < this->maze.size() - 1) {
        vt.coords.first = v.coords.first + 1;
        vt.coords.second = v.coords.second;
        vt.distance = v.distance + 1;
        this->adjacent.push_back(vt);
    }
    if (v.coords.second < this->maze[0].size() - 1) {
        vt.coords.first = v.coords.first;
        vt.coords.second = v.coords.second + 1;
        vt.distance = v.distance + 1;
        this->adjacent.push_back(vt);
    }
}

void PathFinder::printMaze() {
    if (this->maze.empty()) {
        cout << "\033[1;34mno maze found\033[0m\n\n";
        return;
    }
    for (int i  = 0; i < this->maze.size() + 1; ++i) {
        for (int j = 0; j < this->maze[0].size() + 1; ++j) {
            if (i == 0 && j > 0) {
                cout << "\033[1;35m" << ((j - 1) % 10) << "\033[0m ";
                continue;
            } else if (j == 0 && i > 0) {
                cout << "\033[1;35m" << ((i - 1) % 10) << "\033[0m ";
                continue;
            } else if (j == 0 && i == 0) {
                cout << "  ";
            } else if (maze[i - 1][j - 1] == '.') {
                cout << "\033[1;34m.\033[0m ";
            } else if (maze[i - 1][j - 1] == '+') {
                cout << "\033[1;31m+\033[0m ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

void PathFinder::setStart(int row, int col) {
    this->adjacent.clear();
    this->visited.clear();
    this->start = Vertex(row, col, 0);
}

void PathFinder::setDestination(int row, int col) {
    this->adjacent.clear();
    this->visited.clear();
    this->destination = Vertex(row, col, 0);
}

PathFinder::PathFinder() {
    vector<vector<char>> v;
    this->maze = v;
}

bool PathFinder::hasMazeSet() {
    return !this->maze.empty();
}

void PathFinder::setMaze(vector<vector<char>> maze) {
    this->maze = maze;
}