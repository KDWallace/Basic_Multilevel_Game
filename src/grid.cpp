#include "../include/game.hpp"

//load map data from resources/maps and
void Grid::loadMap(std::string fileName, int mapRoom)
{
  try
  {
    this->mapName = fileName;
    //this->mapName = fileName.substr(fileName.find("/")+1);
    this->mapRoom = mapRoom;
    //attempt to find the file in the location specified
    std::ifstream file;
    file.open("../resources/maps/" + fileName + "/map");
    //if the file does not exist, print error
    if (!file)
      std::cerr << "Missing file location: " << fileName << std::endl;
    //if the file does exist
    else
    {
      //for every line in the file, assign it to a slot in the grid array
      std::string tmp;
      //skips lines based on room number
      for (int l = 1; l < mapRoom; l++)
        getline(file,tmp,'\n');
      for (int i = 0; i < DIMY; i++)
      {
        for (int j = 0; j < DIMX; j++)
        {
          //gets line from file, converts to string and sets it to array slot j,i
          getline(file,tmp,' ');
          std::stringstream conv(tmp);
          conv >> Grid::grid[j][i];
        }
      }
      file.close();
    }
  }
  catch (std::exception& e)
  {
    std::cerr << e.what();
  }
}

//prints map to screen
void Grid::printMap()
{
  for (int i = 0; i < DIMY; i++)
  {
    setCursorPosition((getConsoleWidth()/2) - DIMX,4+i);
    for (int j = 0; j < DIMX; j++)
      std::cout << this->convertMap(this->grid[j][i]) << " ";
    //new line at the end of every 12 values (DIM = 12)
    std::cout << std::endl;
  }
}

char Grid::convertMap(int tile)
{
  char tileChar = ' ';

  //locked doors and warp tiles
  if (tile < 0)
  {
    //if the tile value is greater than -1000, it will show as blank and will move the player to room X
    if (tile > -1000)
      if (-tile < this->mapRoom)
        tileChar = '^';
      else
        tileChar = 'v';
    else if (tile > -3000)
      tileChar = '|';
    else
      tileChar = '_';
  }

  //empty space
  else if (tile == 0||tile == 1)
    tileChar = ' ';
  //bolder
  else if (tile == 8)
    tileChar = 'O';
  //invisible wall
  else if (tile == 9)
    tileChar = ' ';
  //wall
  else if (tile == 10)
    tileChar = '#';
  else
    tileChar = '?';
  return tileChar;
}

void Grid::updateMap(Player* player,int* width, int fps)
{
  //refresh rate
  sleep(1000/fps);
  this->incrementFrames();

  //adjests the display if the console is resized
  for (unsigned int i = 0; i < launchers.size(); i++)
  {
    if (launchers[i].getActive())
    {
      int dX = 0, dY = 0;
      if (launchers[i].isHorizontal())
        if (launchers[i].isPositive())
          dX = 1;
        else
          dX = -1;
      else
        if (launchers[i].isPositive())
          dY = 1;
        else
          dY = -1;
      if (launchers[i].update(this->frames))
      {
        Projectile proj;
        proj.setLoc(launchers[i].getLocX()+dX, launchers[i].getLocY()+dY);
        proj.setDirection(launchers[i].isHorizontal(),launchers[i].isPositive());
        proj.setRate(launchers[i].getProjectileRate());
        proj.setChar('*');
        this->projectiles.push_back(proj);
      }
    }
  }

  for (unsigned int i = 0; i < projectiles.size(); i++)
  {
    if(!projectiles[i].update(width,this))
      projectiles.erase(projectiles.begin() + i);
  }
  if (*width != (getConsoleWidth()))
  {
    clearScreen();
    this->printMap();
    //forces player to be printed to screen
    player->prevLocX = -1;
    displayData(player,this);
    *width = getConsoleWidth();
    std::cout.flush();
  }
  player->updateLoc(width);
}
bool Grid::checkTile(int j, int i)
{
  bool clear = false;
  if (this->grid[j][i] == 0 || this->grid[j][i] == 1)
    clear = true;
  return clear;
}
bool Grid::checkTile(int j, int i, char direction, Player *player)
{
  bool clear = false;
  if (this->grid[j][i] == 0 || this->grid[j][i] == 1)
    clear = true;
  if (this->grid[j][i] < 0)
  {
    if (this->grid[j][i] > -1000)
    {
      this->loadMap(this->mapName,-this->grid[j][i]);
      this->projectiles.clear();
      this->launchers.clear();
      this->loadEntities();
      clearScreen();
      this->printMap();
      displayData(player,this);
      player->findSpawn(this);
    }
  }
  //moving bolders
  else if (this->grid[j][i] == 8)
  {
    if (direction == 'w' && (this->grid[j][i-1] == 0||this->grid[j][i-1] == 1))
    {
      this->grid[j][i-1] = 8;
      this->grid[j][i] = 0;
      print((getConsoleWidth()/2) - DIMX + j*2,i-1+4,'O');
      print((getConsoleWidth()/2) - DIMX + j*2,i+4,' ');
      clear = true;
    }
    else if (direction == 's' && (this->grid[j][i+1] == 0||this->grid[j][i+1] == 1))
    {
      this->grid[j][i+1] = 8;
      this->grid[j][i] = 0;
      print((getConsoleWidth()/2) - DIMX + j*2,i+1+4,'O');
      print((getConsoleWidth()/2) - DIMX + j*2,i+4,' ');
      clear = true;
    }
    else if (direction == 'a' && (this->grid[j-1][i] == 0||this->grid[j-1][i] == 1))
    {
      this->grid[j-1][i] = 8;
      this->grid[j][i] = 0;
      print((getConsoleWidth()/2) - DIMX + (j-1)*2,i+4,'O');
      print((getConsoleWidth()/2) - DIMX + j*2,i+4,' ');
      clear = true;
    }
    else if (direction == 'd' && (this->grid[j+1][i] == 0||this->grid[j+1][i] == 1))
    {
      this->grid[j+1][i] = 8;
      this->grid[j][i] = 0;
      print((getConsoleWidth()/2) - DIMX + (j+1)*2,i+4,'O');
      print((getConsoleWidth()/2) - DIMX + j*2,i+4,' ');
      clear = true;
    }
  }
  return clear;
}

std::string Grid::getMapName()
{
  return this->mapName;
}
int Grid::getMapRoom()
{
  return this->mapRoom;
}

void Grid::loadSave(std::string save)
{

}

void Grid::loadEntities()
{

  std::ifstream file;
  file.open("../resources/maps/" + this->mapName + "/objects");
  std::string tmp;
  while (getline(file,tmp))
  {
    std::istringstream iss(tmp);
    iss >> tmp;
    std::stringstream conv(tmp);
    int val;
    conv >> val;
    for (int i = 0; i < DIMY; i++)
      for (int j = 0; j < DIMX; j++)
      {
        if (this->grid[j][i] == val)
        {
          iss >> tmp;
          if (tmp == "Launcher")
          {
            //creates a new launcher
            Launcher launcher;
            iss >> tmp;
            bool tmp3 = false,tmp4 = false;
            if (tmp == "1")
              tmp3 = true;
            iss >> tmp;
            if (tmp == "1")
              tmp4 = true;
            launcher.setDirection(tmp3,tmp4);
            iss >> tmp;
            tmp3 = false;
            if (tmp == "1")
              tmp3 = true;
            launcher.setActive(tmp3);
            iss >> tmp;
            conv >> val;
            launcher.setRate((unsigned int)val);
            iss >> tmp;
            conv >> val;
            launcher.setProjectileRate((unsigned int)val);
            launcher.setLoc(j,i);
            this->launchers.push_back(launcher);
          }
        }
      }
    }
}

void Grid::incrementFrames()
{
  if (this->frames < std::numeric_limits<unsigned int>::max())
    this->frames ++;
  else
    frames = 0;
}

unsigned int Grid::getFrameNumber()
{
  return this->frames;
}
