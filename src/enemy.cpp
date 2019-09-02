#include "../include/game.hpp"

//setters
void Enemy::setHealth(unsigned short health)
{
  this->health = health;
}
void Enemy::setChar(char symbol)
{
  this->symbol = symbol;
}

void Enemy::setLoc(int locX, int locY)
{
  this->locX = locX;
  this->locY = locY;
}

//getters
unsigned short Enemy::getHealth()
{
  return this->health;
}

char Enemy::getChar()
{
  return this->symbol;
}

//other
void Enemy::stalk(Player *player)
{
  if (abs(this->locX + 1 - player->locX) < (abs(this->locX - player->locX)))
    this->locX++;
  else if (abs(this->locX - 1 - player->locX) < (abs(this->locX - player->locX)))
    this->locX--;
  else if (abs(this->locY + 1 - player->locY) < (abs(this->locY - player->locY)))
    this->locY++;
  else if (abs(this->locY - 1 - player->locY) < (abs(this->locY - player->locY)))
    this->locY--;
}

void Enemy::updateLoc(int* width)
{
  if (this->prevLocX != this->locX || this->prevLocY != this->locY)
  {
    print((getConsoleWidth()/2) - DIMX + this->prevLocX*2,this->prevLocY + 4," ");
    print((getConsoleWidth()/2) - DIMX + this->locX*2,this->locY + 4,this->getChar());
    this->prevLocX = this->locX;
    this->prevLocY = this->locY;
    std::cout.flush();
  }
}

void Enemy::findSpawn(Grid *grid)
{
  for (int i = 0; i < DIMY; i++)
    for (int j = 0; j < DIMX; j++)
      if (grid->grid[j][i] == 11)
      {
        this->setLoc(j,i);
        return;
      }
}
