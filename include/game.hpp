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
class Grid;
class Launcher;
class Projectile;
class Button;
class Enemy
{
private:
  char symbol;
  bool alive;
  unsigned short health, damage;
public:
  int locX, locY, prevLocX, prevLocY;
  //setters
  void setLoc(int,int);
  void setHealth(unsigned short);
  void setChar(char);
  //getters
  unsigned short getHealth();
  char getChar();

  //other
  void updateLoc(int*);
  void findSpawn(Grid*);
  void checkHealth();
  void stalk(Player*);
};
class Grid
{
private:
  unsigned int frames = 0;
  std::string mapName;
  std::string fileName;
  int mapRoom;
  std::vector<Enemy> enemies;
  std::vector<Launcher> launchers;
  std::vector<Projectile> projectiles;
  std::vector<Button> buttons;
public:
  void incrementFrames();
  int grid[DIMX][DIMY] = {{0}};
  int getMapRoom();
  unsigned int getFrameNumber();
  std::string getMapName();
  std::string getFileName();
  void loadSave(std::string);
  void loadMap(std::string,int);
  char convertMap(int);
  void printMap();
  void updateMap(Player*,int*,int);
  bool checkTile(int,int,char,Player*);
  bool checkTile(int,int);
  void loadEntities();
};
class Player
{
private:
  char symbol;
  std::string name;
  unsigned short health;
  unsigned short maxHealth;
public:
  int locX, locY, prevLocX, prevLocY;
  //setters
  void setPlayer(std::string,unsigned short,unsigned short,char);
  void setName(std::string);
  void setLoc(int,int);
  void setHealth(unsigned short);
  void setMaxHealth(unsigned short);
  void setChar(char);
  void findSpawn(Grid*);
  //getters
  std::string getName();
  unsigned short getHealth();
  unsigned short getMaxHealth();
  char getChar();
  //handlers
  void moveUp(Grid*);
  void moveDown(Grid*);
  void moveLeft(Grid*);
  void moveRight(Grid*);
  void updateLoc(int*);
};

class Projectile
{
private:
  bool horizontal;
  bool positive;
  int locX,locY,prevLocX = 0,prevLocY = 0;
  char symbol;
  unsigned int rate;
  unsigned int lastUpdate = 0;
public:
  void setDirection(bool,bool);
  void setChar(char);
  void setLoc(int,int);
  void setRate(unsigned int);
  void updateLoc(int*);
  bool update(int*,Grid*);
};

class Launcher
{
private:
  bool horizontal;
  bool positive;
  bool active;
  unsigned int rate;
  unsigned int projectileRate;
  int locX,locY;
  unsigned int timeFired = (unsigned int) 0;
public:
  void setDirection(bool,bool);
  void setActive(bool);
  void setRate(unsigned int);
  void setLoc(int,int);
  void setProjectileRate(unsigned int);

  bool getActive();
  int getLocX();
  int getLocY();
  unsigned int getProjectileRate();
  bool isHorizontal();
  bool isPositive();

  bool update(unsigned int);
};

class Button
{
private:
  bool active;
  bool plate;
  int initial;
  int onLocX, onLocY, changeTo;
public:
  void setActive(bool);
  void connectTo(Grid*,int,int,int);
  void pressurePlate(bool);
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
