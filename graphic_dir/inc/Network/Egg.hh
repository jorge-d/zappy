#ifndef _EGG_H
# define _EGG_H

namespace zappy
{
  class Egg
  {
    unsigned int _x;
    unsigned int _y;
    unsigned char _id;
    unsigned char _father_nbr;
    bool _state;
  public:
    Egg(unsigned char, unsigned char, unsigned int, unsigned int);
    ~Egg();
    void setState();
    unsigned char getId() const;
    unsigned char getTeam() const; 
    bool isGood() const;   
  };
}
#endif
