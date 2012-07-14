#include "excp.hh"
#include "Grid.hh"

namespace zappy
{
  Grid *Grid::instance = NULL;
  Grid::Grid(unsigned int x, unsigned int y, unsigned int t) :
    _time_unit(t), _size_x(x), _size_y(y), _turn(true)
  {
    ;
  }

  Grid::~Grid()
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	it_b = _p_list.erase(it_b);
      }

    std::list<Egg*>::iterator it_e = _eggs.begin();

    for (; it_e != _eggs.end() ; ++it_e)
      {
	it_e = _eggs.erase(it_e);
      }

    std::list<Team*>::iterator it_t = _teams.begin();

    for (; it_t != _teams.end() ; ++it_t)
      {
	it_t = _teams.erase(it_t);
      }

    for (unsigned int i = 0; i < _size_x * _size_y; ++i)
      {
	delete _grid[i];
      }
  }

  std::list<Team*> const &Grid::getTeams() const
  {
    return (_teams);
  }

  int Grid::accessGrid(unsigned int x, unsigned int y)
  {
    return ((y * this->_size_x) + x);
  }

  Box & Grid::getBox(unsigned int x, unsigned  int y)
  {
    int pos = accessGrid(x,y);
    return *_grid.at(pos);
  }

  void Grid::setGrid(unsigned int x, unsigned int y, unsigned int *b)
  {
    unsigned int pos = accessGrid(x,y);
    for (int i = 0; i < 7; ++i)
      _grid[pos]->setElements(b[i], i);
    _grid[pos]->setCoord(x, y);
    if (_turn)
      _listGfx.push_back(pos);
    else
      _listNet.push_back(pos);
  }

  void Grid::endList(void) // true pour le tour du network, false qd gfxlist sera utilisee par ogre
  {
    if (_turn == true)
      _listGfx.clear();
    else
      _listNet.clear();
    _turn = !_turn;
  }

  std::list<unsigned int> &Grid::getUpdatedCoord()
  {
    if (_turn)
      {
        _turn = !_turn;
        _listNet.clear();
        return(_listGfx);
      }
    else
      {
        _turn = !_turn;
        _listGfx.clear();
        return(_listNet);
      }
  }

  void Grid::setPlayerBag(unsigned int x, unsigned int y, unsigned int id, unsigned int *b)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getId() == id)
	  {
	    (*it_b)->setPosition(x, y);
	    for (int i = 0; i < 7; ++i)
	      (*it_b)->setBag(b[i], static_cast<Elements>(i));
	    break;
	  }
      }
  }

  void Grid::setPlayerTBag(unsigned int id, Elements i)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getId() == id)
	  {
	    (*it_b)->setToBag(i);
	    break;
	  }
      }
  }

  void Grid::setPlayerFBag(unsigned int id, Elements i)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getId() == id)
	  {
	    (*it_b)->setFromBag(i);
	    break;
	  }
      }
  }

  void Grid::setPlayerLevel(unsigned int n, unsigned int l)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getId() == n)
	  {
	    (*it_b)->setLevel(l);
	    if ((*it_b)->getState() == BEG_SPELLING)
	      (*it_b)->setState(END_SPELLING);
	    break;
	  }
      }
  }

  void Grid::setPlayerPosition(unsigned int x, unsigned int y, unsigned int n, unsigned int o)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getId() == n)
	  {
	    (*it_b)->setPosition(x, y);
	    (*it_b)->setOrientation(o);
	    break;
	  }
      }
  }

  void Grid::setPlayerMessage(unsigned int id, std::string s)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getId() == id)
	  {
	    (*it_b)->setBroadcast(s);
	    break;
	  }
      }
  }

  void Grid::setPlayerState(unsigned int id, State e)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getId() == id)
	  {
	    (*it_b)->setState(e);
	    break;
	  }
      }
  }

  void Grid::setEggState(unsigned int l, bool b)
  {
    std::list<Egg*>::iterator it_b = _eggs.begin();

    for (; it_b != _eggs.end() ; ++it_b)
      {
	if ((*it_b)->getId() == l)
	  {
	    if (b)
	      (*it_b)->setState();
	    else
	      it_b = _eggs.erase(it_b);
	    break;
	  }
      }
  }

  void Grid::setMapSize(unsigned int x, unsigned int y)
  {
    _size_x = x;
    _size_y = y;
    if (_size_x != 0)
      {
	_grid.resize(_size_x * _size_y);
	for (unsigned int i = 0; i < (_size_x * _size_y); ++i)
	  _grid[i] = new Box();
      }
  }

  void Grid::setTimeUnit(unsigned int t)
  {
    _time_unit = t;
  }

  void Grid::addPlayer(Player &p)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();
    bool f = true;

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getId() == p.getId())
	  {
	    *(*it_b) = p;
	    f = false;
	    return ;
	  }
      }
    if (f)
      _p_list.push_back(&p);
  }

  void Grid::addEgg(Egg &p)
  {
   std::list<Egg*>::iterator it_b = _eggs.begin();

    for (; it_b != _eggs.end() ; ++it_b)
      {
	if ((*it_b)->getId() == p.getId())
	  {
	      (*it_b)->setState();
	    return ;
	  }
      }
    _eggs.push_back(&p);
  }

  void Grid::setWinners(std::string const &s)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getTeamStr() == s)
	  (*it_b)->setState(WINNER);
      }
  }

  unsigned int Grid::getIdFromName(std::string const &s)
  {
    std::list<Team*>::iterator it_b = _teams.begin();

    for (; it_b != _teams.end() ; ++it_b)
      {
	if ((*it_b)->getTeamName() == s)
	  return (*it_b)->getTeamId();
      }
    return -1;
  }

  void Grid::addTeamNames(std::string const &s)
  {
    static unsigned int i = 0;

    Team *t = new Team(i, s);
    ++i;
    _teams.push_back(t);
  }

  Grid & Grid::getInstance()
  {
    if (instance == NULL)
      instance = new Grid(0,0,0);
    return (*instance);
  }

  void Grid::initInstance()
  {
    if (instance == NULL)
      instance = new Grid(0,0,0);
  }

  unsigned int Grid::getTime() const{
    return _time_unit;
  }

  unsigned int Grid::getX() const{
    return _size_x;
  }

  unsigned int Grid::getY() const{
    return _size_y;
  }

  std::vector<zappy::Box*> &Grid::getBoxes()
  {
    return _grid;
  }

  std::list<zappy::Player*> &Grid::getPlayers(){
    return _p_list;
  }

  Player *Grid::getPlayer(unsigned int id)
  {
    std::list<Player*>::iterator it_b = _p_list.begin();

    for (; it_b != _p_list.end() ; ++it_b)
      {
	if ((*it_b)->getId() == id)
	  return (*it_b);
      }
    throw (excp("bad player"));
  }

  std::list<zappy::Egg*> &Grid::getEggs()
  {
    return _eggs;
  }

  Egg &Grid::getEgg(unsigned int id)
  {
    std::list<Egg*>::iterator it_b = _eggs.begin();

    for (; it_b != _eggs.end() ; ++it_b)
      {
	if ((*it_b)->getId() == id)
	  return *(*it_b);
      }
    throw (excp("bad player"));
  }

}
