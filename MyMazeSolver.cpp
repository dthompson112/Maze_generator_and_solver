//#include <iostream>
#include <ics46/factory/DynamicFactory.hpp>
#include "MyMazeSolver.hpp"
#include "Maze.hpp"
#include <random>
#include "MazeSolution.hpp"
ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver,MyMazeSolver, "Dans Solver(Required)");

std::default_random_engine eng{std::random_device{}()};
std::uniform_int_distribution<int> dist{0,3};

MyMazeSolver::MyMazeSolver(){

}

MyMazeSolver::~MyMazeSolver(){
for(int i = 0; i < h; ++i)
    delete[] visited[i];
    delete[] visited;
}


int MyMazeSolver::hasVisited(int x, int y){
    if(x < 0 || x > w-1 || y < 0 || y > h - 1)
    return 1;
    if(visited[y][x] == 1)
    return 1;
    return 0;
}


void MyMazeSolver::solveMaze(const Maze& maze,MazeSolution & mazeSolution){
h = maze.getHeight();
w = maze.getWidth();

visited = new int * [h];
for(int i = 0; i < h; ++i){
    visited[i] = new int[w];    
}

for(int i = 0; i < h; ++i)
for(int j = 0; j < w; ++j)
visited[i][j] = 0;

solve(maze, 0,0, mazeSolution);
}





void MyMazeSolver::solve(const Maze& mz,int x, int y, MazeSolution & ms){

if(ms.isComplete())
return;

visited[y][x] = 1;
 uWall = 0;
 dWall = 0;
 lWall = 0;
 rWall = 0;

xValue = x;
yValue = y;


if( mz.wallExists(x,y,Direction::up) || hasVisited(x,y - 1)){
uWall = 1;
}
if(mz.wallExists(x,y,Direction::down) ||  hasVisited(x, y + 1)){
dWall = 1;
}
if(mz.wallExists(x,y,Direction::left) || hasVisited(x - 1, y)){
lWall = 1;
}
if(mz.wallExists(x,y,Direction::right) || hasVisited(x + 1,y))
rWall = 1;

if(!rWall || !uWall || !dWall || !lWall){
    ms.extend(chsDirection(uWall,dWall,lWall,rWall));
    solve(mz,xValue,yValue,ms);
   if(ms.isComplete()) return;    
   ms.backUp();
   solve(mz,x,y,ms);
   }

}


Direction MyMazeSolver::chsDirection(int u, int d, int l, int r){

while(true){

if(r == 0){
    ++xValue;
    return Direction::right;
    }

if(d == 0){
    ++yValue;
    return Direction::down;
    }

if(l == 0){
    --xValue;
    return Direction::left;
    }
    
if(u == 0){
    //choose dirction and update coordinates
    --yValue;
    return Direction::up;
    }
}

}
