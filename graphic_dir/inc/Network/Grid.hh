#ifndef _GRID_H
# define _GRID_H

#include <vector>
#include <list>
#include <string>

#include "Box.hh"
#include "Egg.hh"
#include "Player.hh"
//#include "SafeQueue.hpp"
#include "Team.hh"

namespace zappy
{
  class Grid
  {
    unsigned int _time_unit;
    unsigned int _size_x;
    unsigned int _size_y;

    std::vector<zappy::Box*> _grid;

    std::list<zappy::Player*> _p_list;
    std::list<zappy::Egg*> _eggs;

    std::list<zappy::Team*> _teams;
    //    SafeQueue<unsigned int> _coord_update;
    std::list<unsigned int> _listGfx;
    std::list<unsigned int> _listNet;

    bool _turn;
    static Grid *instance;

    Grid(unsigned int x, unsigned int y, unsigned int t);

  public:

    ~Grid();
    int	 accessGrid(unsigned int x, unsigned int y) ;
    zappy::Box &getBox(unsigned int, unsigned int) ;
    void setGrid(unsigned int x, unsigned int y, unsigned int *b);
    void setPlayerTBag(unsigned int id, Elements r);
    void setPlayerFBag(unsigned int id, Elements r);
    void setPlayerBag(unsigned int , unsigned int , unsigned int,  unsigned int *);
    void setPlayerLevel(unsigned int n, unsigned int l);
    void setPlayerMessage(unsigned int ,std::string s);
    void setPlayerPosition(unsigned int x, unsigned int y, unsigned int n, unsigned int l);
    void setPlayerState(unsigned int , State i);
    void setEggState(unsigned int l, bool b);
    void setMapSize(unsigned int x, unsigned int y);
    void setTimeUnit(unsigned int t);
    void addPlayer(Player &);
    void addEgg(Egg &);
    void endList();
    void setWinners(std::string const &);
    void setSpellSuccess(unsigned int x, unsigned y);
    std::list<Team*> const &getTeams() const;
    void addTeamNames(std::string const &);
    static Grid & getInstance();
    void initInstance();
    unsigned int getIdFromName(std::string const &s);
    unsigned int getX() const;
    unsigned int getY() const;
    unsigned int getTime() const;
    std::list<unsigned int> &getUpdatedCoord();
    Egg &getEgg(unsigned int id);
    std::list<zappy::Egg*> &getEggs();
    Player *getPlayer(unsigned int id);
    std::list<zappy::Player*> &getPlayers();
    std::vector<zappy::Box*> &getBoxes();
  };
}

#endif
