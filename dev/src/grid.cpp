#include "../include/mapmaker.hpp"

//prints map to screen
void Grid::printMap()
{
  for (int i = 0; i < DIMY; i++)
  {
    setCursorPosition((getConsoleWidth()/2) - DIMX,4+i);
    for (int j = 0; j < DIMX; j++)
      std::cout << "[" << this->convertMap(this->grid[j][i]) << "] ";
    //new line at the end of every 36 values (DIM = 36)
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
    tileChar = 'i';
  //wall
  else if (tile == 10)
    tileChar = '#';
  else
    tileChar = '?';
  return tileChar;
}

void Grid::saveMap()
{
  //allows the user to name the file
  std::cout << "Save file as: ";
  std::string filename;
  std::cin >> filename;

  //allows the user to choose what room this map represents
  int room;
  std::cout << "Room number: ";
  std:cin >> room;

  //tests the file to see if it exists
  std::ifstream file;
  file.open(filename+"/map");

  //if the file does previously exist
  if (file)
  {
    std::string strRoom = "", strTmp;
    int roomTmp = 0;
    //copy the file for before the room number and after the room number
    while (std::getline(file,strTmp))
    {
      //if the current line is less than the room number, add it to the room string
      roomTmp++;
      if (roomTmp < room)
      {
        strRoom += strTmp;
      }

      //if the current string number is the same as the room number, ignore that line and add the new string
      else if (roomTmp == room)
      {
        strRoom += grid;
      }

      //otherwise, if the line is after the room number, continue adding it to the string
      else
      {
        strRoom += strTmp;
      }

      //add a new line to the end of each line
      strTmp += "\n";
    }
    //clears the tmp variable from memory
    strTmp.clear();

  }
  else
  {

  }
}
