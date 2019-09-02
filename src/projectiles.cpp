#include "../include/game.hpp"

void Projectile::setDirection(bool horizontal, bool positive)
{
  this->horizontal = horizontal;
  this->positive = positive;
}

void Projectile::setChar(char symbol)
{
  this->symbol = symbol;
}

void Projectile::setLoc(int locX, int locY)
{
  this->locX = locX;
  this->locY = locY;
}

void Projectile::setRate(unsigned int rate)
{
  this->rate = rate;
}

bool Projectile::update(int* width, Grid* grid)
{
  if (grid->getFrameNumber() > this->rate + this->lastUpdate)
  {
    int dX = 0;
    this->prevLocX = this->locX;
    this->prevLocY = this->locY;
    if (this->positive)
      dX = 1;
    else
      dX = -1;
    if (this->horizontal)
      this->locX += dX;
    else
      this->locY += dX;
    if (grid->checkTile(this->locX,this->locY))
    {
      this->updateLoc(width);
      this->lastUpdate = grid->getFrameNumber();
    }
    else
      return false;
  }
  return true;
}

void Projectile::updateLoc(int* width)
{
  if (this->prevLocX != this->locX || this->prevLocY != this->locY)
  {
    print((getConsoleWidth()/2) - DIMX + this->prevLocX*2,this->prevLocY + 4," ");
    print((getConsoleWidth()/2) - DIMX + this->locX*2,this->locY + 4,this->symbol);
    this->prevLocX = this->locX;
    this->prevLocY = this->locY;
    std::cout.flush();
  }
}



void Launcher::setDirection(bool horizontal, bool positive)
{
  this->horizontal = horizontal;
  this->positive = positive;
}

void Launcher::setActive(bool active)
{
  this->active = active;
}

void Launcher::setRate(unsigned int rate)
{
  this->rate = rate;
}

void Launcher::setLoc(int locX, int locY)
{
  this->locX = locX;
  this->locY = locY;
}

bool Launcher::getActive()
{
  return this->active;
}

int Launcher::getLocX()
{
  return this->locX;
}

int Launcher::getLocY()
{
  return this->locY;
}

bool Launcher::isHorizontal()
{
  return this->horizontal;
}

bool Launcher::isPositive()
{
  return this->positive;
}

bool Launcher::update(unsigned int frame)
{
  bool fire = false;
  if (frame > this->timeFired + this->rate)
  {
    this->timeFired = frame;
    fire = true;
  }
  return fire;
}

void Launcher::setProjectileRate(unsigned int rate)
{
  this->projectileRate = rate;
}

unsigned int Launcher::getProjectileRate()
{
  return this->projectileRate;
}


void Button::setActive(bool active)
{
  this->active = active;
}

void Button::connectTo(Grid* grid,int locX,int locY,int changeTo)
{
  this->initial = grid->grid[locX][locY];
  grid->grid[locX][locY] = changeTo;
}

void Button::pressurePlate(bool plate)
{
  this->plate = plate;
}
