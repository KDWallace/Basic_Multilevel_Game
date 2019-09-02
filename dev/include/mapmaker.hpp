#ifndef GAME_HPP
#define GAME_HPP

//libraries
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <ctime>
#include <vector>
#include <limits>
//OS dependant libraries
#ifdef _WIN32
#include <windows.h>
#include <conio.h>
void sleep(unsigned milliseconds)
{
  Sleep(milliseconds);
}
int getConsoleWidth()
{
  CONSOLE_SCREEN_BUFFER_INFO dimensions;
  GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),&dimensions);
  return dimensions.dwSize.X;
}
#else
#include <unistd.h>
void sleep(unsigned milliseconds)
{
  usleep(milliseconds*1000);
}
#endif

//definitions
#define DIMX 36
#define DIMY 24
#define GAMEVERSION "Dungeon Crawler V0.1"
//classes
class Player;
class Grid
{
private:
  unsigned int frames = 0;
  std::string mapName;
  std::string fileName;
  int mapRoom;
public:
  void incrementFrames();
  int grid[DIMX][DIMY] = {{0}};
  int getMapRoom();
  unsigned int getFrameNumber();
  std::string getMapName();
  std::string getFileName();
  void saveMap();
  void loadMap(std::string,int);
  char convertMap(int);
  void printMap();
  void updateMap(Player*,int*,int);
  bool checkTile(int,int,char,Player*);
  bool checkTile(int,int);
};
class Player
{
private:
  char symbol;
public:
  int locX, locY, prevLocX, prevLocY;
  //setters
  void setPlayer(std::string,unsigned short,unsigned short,char);
  void setLoc(int,int);
  void setChar(char);
  void findSpawn(Grid*);
  //getters
  char getChar();
  //handlers
  void moveUp(Grid*);
  void moveDown(Grid*);
  void moveLeft(Grid*);
  void moveRight(Grid*);
  void updateLoc(int*);
};

//control methods
void userInput(char,Player*, Grid *grid);
void setCursorPosition(int,int);
void clearScreen();
void print(int,int,std::string);
void print(int,int,char);
void displayData(Player*,Grid*);
void updateHealth(Player*);

#endif
