#include <ics46/factory/DynamicFactory.hpp>
#include "MyMazeGenerator.hpp"
#include "Maze.hpp"
#include <cstdlib>
#include "Direction.hpp"
#include <random>
ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator,MyMazeGenerator, "Dan's Generator(Required)");

std::default_random_engine engine{std::random_device{}()};
std::uniform_int_distribution<int> distribution{0,3};

MyMazeGenerator::MyMazeGenerator(){

}

MyMazeGenerator::~MyMazeGenerator(){
   for(int i = 0; i < h; ++i)
    delete[] visited[i];
    delete[] visited;
}

void MyMazeGenerator::generateMaze(Maze& maze){

maze.addAllWalls();

h = maze.getHeight();
w = maze.getWidth();

visited = new int*[h];
for(int i = 0; i < h; ++i)
visited[i] = new int[w];

//Initialize the array
for(int i = 0; i < h; ++i)
for(int j = 0; j < h; ++j)
visited[i][j] = 0;


buildMaze(maze, 0,0);
}

void MyMazeGenerator::buildMaze(Maze& mz, int x, int y){
    visited[y][x] = 1;
    xValue = x; //used to update once direction is choosen
    yValue = y;
    lVisited = hasVisited(x-1,y);
    rVisited = hasVisited(x+1,y);
    uVisited = hasVisited(x,y-1);
    dVisited = hasVisited(x,y+1);
    
    if(!lVisited || !rVisited || !uVisited || !dVisited){
    mz.removeWall(x,y,chooseDirection(uVisited, dVisited,lVisited,rVisited));
    buildMaze(mz,xValue,yValue);
    buildMaze(mz,x,y);
    
    }
}

int MyMazeGenerator::hasVisited(int x, int y){
    if(x < 0 || x > w-1 || y < 0 || y > h-1)
    return 1;
else if(visited[y][x] == 1)
    return 1;
    return 0;
}

Direction MyMazeGenerator::chooseDirection(int u, int d, int l, int r){
    int rv;
    
    while(true){
    rv = distribution(engine);
    if(rv == 0 && u == 0){
        //choose direction and update coordinates
        --yValue;
        return Direction::up;
        }
    if(rv == 1 && d == 0){
        ++yValue;
        return Direction::down;
        }
    if(rv == 2 && l == 0){
        --xValue;
        return Direction::left;
        }
    if(rv == 3 && r == 0){
        ++xValue;
        return Direction::right;
        }
        
    }
}
