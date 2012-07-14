#include <cstring>
#include "Box.hh"

namespace zappy
{
  Box::Box() :
    _x(0), _y(0)
  {
    bzero(_elements, 7);
  }

  Box::~Box()
  {
    ;
  }

  unsigned int* Box::getElements() const
  {
    return (const_cast<unsigned int*>(_elements));
  }

  void Box::setElements(unsigned int e, unsigned int t)
  {
    _elements[t] = e;
  }

  void Box::setCoord(unsigned int x, unsigned int y)
  {
    this->_x = x;
    this->_y = y;
  }

  unsigned int Box::getX(void) const
  {
    return this->_x;
  }

  unsigned int Box::getY(void) const
  {
    return this->_y;
  }
}
