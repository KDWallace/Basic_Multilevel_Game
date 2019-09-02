#include "../include/game.hpp"

//setters
void Player::setPlayer(std::string name,unsigned short health,unsigned short maxHealth,char symbol)
{
  this->setName(name);
  this->setHealth(health);
  this->setMaxHealth(maxHealth);
  this->setChar(symbol);
}
void Player::setName(std::string name)
{
  this->name = name;
}
void Player::setLoc(int locX, int locY)
{
  this->locX = locX;
  this->locY = locY;
}
void Player::setHealth(unsigned short health)
{
  this->health = health;
}
void Player::setMaxHealth(unsigned short health)
{
  this->maxHealth = health;
}
void Player::setChar(char symbol)
{
  this->symbol = symbol;
}
//getters
std::string Player::getName()
{
  return this->name;
}
unsigned short Player::getHealth()
{
  return this->health;
}
unsigned short Player::getMaxHealth()
{
  return this->maxHealth;
}
char Player::getChar()
{
  return this->symbol;
}
void Player::moveUp(Grid *grid)
{
  if (grid->checkTile(this->locX,this->locY-1,'w',this))
  {
    this->prevLocY = this->locY;
    this->locY -= 1;
  }
}
void Player::moveDown(Grid *grid)
{
  if (grid->checkTile(this->locX,this->locY+1,'s',this))
  {
    this->prevLocY = this->locY;
    this->locY += 1;
  }
}
void Player::moveLeft(Grid *grid)
{
  if (grid->checkTile(this->locX - 1,this->locY,'a',this))
  {
    this->prevLocX = this->locX;
    this->locX -= 1;
  }
}
void Player::moveRight(Grid *grid)
{
  if (grid->checkTile(this->locX + 1,this->locY,'d',this))
  {
    this->prevLocX = this->locX;
    this->locX += 1;
  }
}
void Player::updateLoc(int* width)
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

void Player::findSpawn(Grid *grid)
{
  for (int i = 0; i < DIMY; i++)
    for (int j = 0; j < DIMX; j++)
      if (grid->grid[j][i] == 1)
      {
        this->setLoc(j,i);
        return;
      }
}
