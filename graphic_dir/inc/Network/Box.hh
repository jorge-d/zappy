#ifndef _BOX_H
# define _BOX_H

namespace zappy
{
  enum Elements
    {
      FOOD,
      LINEMATE,
      DERAUMERE,
      SIBUR,
      MENDIANE,
      PHIRAS,
      THYSTAME
    };

  class Box
  {
  private:
    unsigned int _elements[7];
    unsigned int _x;
    unsigned int _y;

  public:
    unsigned int* getElements() const;
    void setElements(unsigned int, unsigned int);
    void setCoord(unsigned int x, unsigned int y);
    unsigned int getY(void) const;
    unsigned int getX(void) const;

    Box();
    ~Box();
  };
}

#endif
