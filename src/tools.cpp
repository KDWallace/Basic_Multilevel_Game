#include "../include/game.hpp"
//GUI
void displayData(Player* player,Grid *grid)
{
  print((getConsoleWidth()/2)-grid->getMapName().length(),2,grid->getMapName());
  std::stringstream ss;
  ss << grid->getMapRoom();
  std::string room = ss.str();
  print((getConsoleWidth()/2)+1,2,room);
  print((getConsoleWidth()/2)-player->getName().length(),DIMY+6,player->getName());
  for (int i = 0; i < player->getHealth(); i++)
    print(2+(getConsoleWidth()/2)-player->getHealth()+(3*i)+player->getName().length(),DIMY+6,"<3");
}
void updateHealth(Player* player)
{
  for (int i = 0; i < player->getHealth(); i++)
    print(8+i+player->getName().length(),DIMY+3,"<3");
  if (player->getHealth() < player->getMaxHealth())
    for (int i = 0; i < player->getMaxHealth()-player->getHealth(); i++)
      print(8+i+player->getHealth()+player->getName().length(),DIMY+3,' ');
}

//player input
void userInput(char input, Player* player, Grid* grid)
{
  if (input == 'w')
    player->moveUp(grid);
  else if (input == 's')
    player->moveDown(grid);
  else if (input == 'a')
    player->moveLeft(grid);
  else if (input == 'd')
    player->moveRight(grid);
}

void setCursorPosition(int x, int y)
{
    static const HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    std::cout.flush();
    COORD coord = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(hOut, coord);
}
void clearScreen()
{
  for (int i = 0; i < 60; i++)
  {
    setCursorPosition(0,i);
    std::cout<<"                                                                                                                                                                                                                                               ";
  }
  setCursorPosition(0,0);
}

void print(int x, int y, std::string buffer)
{
  setCursorPosition(x,y);
  std::cout<<buffer;
  setCursorPosition(0,0);
}
void print(int x, int y, char buffer)
{
  setCursorPosition(x,y);
  std::cout<<buffer;
  setCursorPosition(0,0);
}
