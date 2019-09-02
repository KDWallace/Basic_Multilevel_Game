#include "grid.cpp"
#include "player.cpp"
#include "enemy.cpp"
#include "tools.cpp"
#include "projectiles.cpp"
#include "menu.cpp"
#include "../include/game.hpp"

int main()
{
  clearScreen();
  //creates objects
  Grid grid;
  Player player;
  int width = getConsoleWidth();
  //initialises player variables
  player.setPlayer("Dave",5,5,'@');

  //loads map
  grid.loadMap("testmap",1);
  player.findSpawn(&grid);
  //prints map
  grid.loadEntities();
  grid.printMap();
  displayData(&player,&grid);
  while(true)
  {
    grid.updateMap(&player,&width,24);
    //if there is a keypress
    if (kbhit())
    {
      //obtains character press
      char c = getch();
      //q will break the program (for testing)
      if(c == 'q')
        break;
      //otherwise will be taken as input
      else
        userInput(c,&player,&grid);
    }
  }
  clearScreen();
  return 0;
}
