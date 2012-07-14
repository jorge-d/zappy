#include "Egg.hh"

namespace zappy
{
  Egg::Egg(unsigned char i, unsigned char n, unsigned int x, unsigned int y) : _x(x), _y(y), _id(i), _father_nbr(n), _state(true)
  {
    ;
  }

  Egg::~Egg()
  {
    ;
  }

  unsigned char Egg::getId() const
  {
    return (_id);
  }

  unsigned char Egg::getTeam() const
  {
    return (_father_nbr);
  }

  void Egg::setState()
  {
    _state = false;
  }

  bool Egg::isGood() const
  {
    return (_state);
  }
}
