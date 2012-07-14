// Header
// Header
// Header
// Header
// Header
// Header
// Header
// Header

#include <cstring>
#include "Box.hh"
#include "Player.hh"

namespace zappy
{
  Player::Player(unsigned int i, unsigned int x, unsigned int y, unsigned int l, unsigned int o, const char *ts, unsigned int tn,  State s) :
    _x(x), _y(y), _level(l), _or(o), _team_str(ts), _team_nbr(tn), _id(i),  _state(s), _isRendered(false)
  {
    bzero(_bag, sizeof(int) * 7);
  }

  Player::~Player()
  {
    ;
  }

  Player& Player::operator=(Player &p)
  {
    if (this != &p)
      {
	_x = p._x;
	_y = p._y;
	_id = p._id;
	_state = IDLE;
	_isRendered = true;
	bzero(_bag, sizeof(int) * 7);
	_level = p._level;
	_or = p._or;
	_team_str = p._team_str;
	_bdt = p._bdt;
	_team_nbr = p._team_nbr;
      }
    return (*this);
  }

  unsigned int Player::getTeamNbr() const
  {
    return (_team_nbr);
  }

  std::string const & Player::getTeamStr() const
  {
    return (_team_str);
  }

  unsigned int Player::getOrientation() const
  {
    return (_or);
  }

  unsigned int Player::getId() const
  {
    return (_id);
  }

  unsigned int Player::getBag(Elements t) const
  {
    return (_bag[t]);
  }

  const unsigned int *Player::getAllBag(void) const
  {
    return this->_bag;
  }

  std::string const &Player::getMsg() const
  {
    return _bdt;
  }

  bool Player::isTalking() const
  {
    return (_bdt.empty());
  }

  State Player::getState() const
  {
    return _state;
  }

  unsigned int Player::getX(void) const
  {
    return this->_x;
  }

  unsigned int Player::getY(void) const
  {
    return this->_y;
  }

  unsigned int Player::getLevel() const
  {
    return this->_level;
  }

  void Player::setState(State s)
  {
    _state = s;
  }

  void Player::setBroadcast(std::string &s)
  {
    _bdt = s;
  }

  void Player::setLevel(unsigned int l)
  {
    _level = l;
  }

  void Player::setOrientation(unsigned int o)
  {
    _or = o;
  }

  void Player::setBag(unsigned int e, Elements t)
  {
    _bag[t] = e;
  }

  void Player::setPosition(unsigned int x, unsigned int y)
  {
    _x = x;
    _y = y;
  }

  void Player::setFromBag(Elements t)
  {
    --_bag[t];
  }


  void Player::setToBag(Elements t)
  {
    ++_bag[t];
  }

  void Player::setRendered(bool rendered)
  {
    this->_isRendered = rendered;
  }

  bool Player::isRendered(void) const
  {
    return this->_isRendered;
  }
}
