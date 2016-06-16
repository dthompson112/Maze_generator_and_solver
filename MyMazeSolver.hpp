#ifndef MYMAZESOLVER_HPP
#define MYMAZESOLVER_HPP

#include "MazeSolver.hpp"
#include "Maze.hpp"

class MyMazeSolver: public MazeSolver
{
    public:
    MyMazeSolver();
    ~MyMazeSolver();
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution);
    void solve(const Maze& mz,int x, int y, MazeSolution& ms);
    Direction chsDirection(int u, int d, int l, int r);    
    int hasVisited(int x, int y);
    bool solve2(const Maze& maze, int x, int y, MazeSolution& ms);

    private:
    int h;  //heidth
    int w;  //width
    int ** visited;
    int xValue = 0;
    int yValue = 0;
    int lWall = 0;
    int rWall = 0;
    int uWall = 0;
    int dWall = 0;

};




#endif
