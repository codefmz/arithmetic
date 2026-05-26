#ifndef _ITERATE_H_
#define _ITERATE_H_

class Queue {
public:
    Queue();
private:
    int arr[8];
    int count;
    bool judge(int n);
    void set(int i);
};

class Maze
{
public:
    Maze(int row, int col);
    void mazeInitialize();
    bool findWay(int i, int j);
    void printMaze() const;
    ~Maze();
private:
    int** maze;
    int count;
    int row;
    int col;
};


void honoi(int n, char x, char y, char z);

#endif