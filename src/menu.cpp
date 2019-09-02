#include "../include/game.hpp"

class Menu
{
private:
  std::string title;
  std::vector<std::string> slots;
  unsigned int pos, prevPos;
public:
  void initialise(std::string title)
  {
    this->pos = 0;
    this->prevPos = 1;
    this->title = title;
    if (title == GAMEVERSION)
    {
      this->slots = {"New Game","Load Game","Map maker","Options","Exit"};
    }
  }
  void refresh()
  {
    clearScreen();
    print((getConsoleWidth()/2)-(this->title.length()/2),2,this->title);
    for (unsigned int i = 0; i < this->slots.size(); i++)
      print((getConsoleWidth()/2)-(this->slots[i].length()/2),3+i,this->slots[i]);
    this->printCurser();
  }
  void printCurser()
  {
    if (this->prevPos != this->pos)
    {
      print((getConsoleWidth()/2)-(this->slots[this->prevPos].length()/2)-1,3+this->prevPos,' ');
      print((getConsoleWidth()/2)+(this->slots[this->prevPos].length()/2)+1,3+this->prevPos,' ');
      print((getConsoleWidth()/2)-(this->slots[this->pos].length()/2)-1,3+this->pos,'[');
      print((getConsoleWidth()/2)+(this->slots[this->pos].length()/2)+1,3+this->pos,']');
      this->prevPos = this->pos;
    }
  }
  void select(std::string slot, Grid *grid, Player *player)
  {
    if (slot == "New Game")
    {
      //initialises player variables
      clearScreen();
      std::cout << "Enter playerName: ";
      std::string name = "";
      std::cin >> name;
      player->setPlayer(name,5,5,'@');

      //loads map
      grid->loadMap("testmap",1);
      player->findSpawn(grid);
      //prints map
      grid->loadEntities();
    }
  }
  void moveCurser(char input, Grid *grid, Player *player)
  {
    if (input == 'w' && this->pos > 0)
      this->pos -= 1;
    else if (input == 's' && this-> pos < this->slots.size())
      this->pos += 1;
    else if (input == '\n')
      select(this->slots[this->pos], grid, player);
  }

};
