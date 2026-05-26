#include "iterate.h"
#include <cmath>
#include <iostream>

using namespace std;

Queue::Queue() : arr {0}, count {0} {
    set(0);
}

bool Queue::judge(int n) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == arr[n] || abs(i - n) == abs(arr[i] - arr[n])) {
            return false;
        }
    }

    return true;
}

void Queue::set(int i) {
    if (i == 8) {
        for (int j = 0; j < 8; j++) {
            cout << arr[j] << " ";
        }
        count++;
        cout << endl;
        return;
    }

    for (int n = 1; n <= 8; n++) {
        arr[i] = n;
        if (judge(i)) {
            set(i + 1);
        }
    }
}

Maze::Maze(int row, int col) : row(row), col(col), count(0) {
    maze = new int*[row];
    for (size_t i = 0; i < row; i++) {
        maze[i] = new int[col];
    }

    for (size_t i = 0; i < row; i++) {
        for (size_t j = 0; j < col; j++) {
            if (i == 0 || i == row - 1) {
                maze[i][j] = 1;
            } else if (j == 0 || j == col - 1) {
                maze[i][j] = 1;
            } else {
                maze[i][j] = 0;
            }
        }
    }
}

void Maze::mazeInitialize() {
    maze[3][1] = 1;
    maze[3][2] = 1;
    maze[3][3] = 1;
}

bool Maze::findWay(int i, int j) {
    if (maze[row - 2][col - 2] == 2) {
        return true;
    } else if (maze[i][j] == 0) {
        maze[i][j] = 2;
        ++count;
        //右下上左
        if (findWay(i, j + 1) || findWay(i + 1, j) || findWay(i - 1, j) || findWay(i, j - 1)) {
            return true;
        } else {
            maze[i][j] = 3;
            return false;
        }
    }

    return false;
}

void Maze::printMaze() const {
    for (int i = 0; i < row; ++i) {
        for (int j = 0; j < col; ++j) {
            cout << maze[i][j] << " ";
        }
        cout << endl;
    }
}

Maze::~Maze() {
    for (int i = 0; i < 7; ++i) {
        delete[] maze[i];
    }
}

void move(int n, char x, char y) {
    cout << "move " << n << " from " << x << " to " << y << endl;
}

void honoi(int n, char x, char y, char z) {
    if (n == 1) {
        move(1, x, z);
        return;
    }

    if (n > 1) {
        honoi(n - 1, x, z, y);
        move(n, x, z);
        honoi(n - 1, y, x, z);
    }
}