#ifndef MYMAZEGENERATOR_HPP
#define MYMAZEGENERATOR_HPP
#include "MazeGenerator.hpp"
#include "Direction.hpp"

class MyMazeGenerator: public MazeGenerator
{
   public:
   MyMazeGenerator();
   ~MyMazeGenerator();
   void initVisited(); 
   void generateMaze(Maze& maze);
   void buildMaze(Maze& mz, int x, int y);
   int hasVisited(int row, int column);
   int randomValue();
   Direction chooseDirection(int u, int d, int l,int r);

   private:
   int ** visited;
   int index = 0;
   int h;
   int w;
   int xValue = 0;
   int yValue = 0;
   int vCounter;
   int lVisited,rVisited,uVisited,dVisited;
};

#endif
