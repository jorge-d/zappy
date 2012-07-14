#ifndef _PLAY_H
# define _PLAY_H

//#include "OgreMain.h"
#include "Box.hh"
#include <string>
namespace zappy
{
  enum State
    {
      MOVING,
      BEG_SPELLING,
      FORKING,
      EXPULSING,
      BROADCASTING,
      TAKING,
      DROPPING,
      IDLE,
      DYING,
      NONE,
      END_SPELLING,
      WINNER
    };

  class Player
  {
    unsigned int _x;
    unsigned int _y;
    unsigned char _level;
    unsigned char _or;
    std::string _team_str;
    unsigned int _team_nbr;
    unsigned int _id;
    unsigned int _bag[7];
    State _state;
    std::string _bdt;
    bool _isRendered;

  public:
    std::string const& getTeamStr() const;
    unsigned int getTeamNbr() const;
    unsigned int getOrientation() const;
    unsigned int getLevel() const;
    unsigned int getId() const;
    unsigned int getBag(Elements t) const;
    const unsigned int *getAllBag(void) const;
    unsigned int getX(void) const;
    unsigned int getY(void) const;
    bool isTalking() const;
    State getState() const;
    std::string  const &getMsg() const;
    void setLevel(unsigned int);
    void setPosition(unsigned int, unsigned int);
    void setOrientation(unsigned int);
    void setState(unsigned int);
    void setBag(unsigned int e, Elements t);
    void setFromBag(Elements e);
    void setToBag(Elements e);
    void setBroadcast(std::string &s);
    void setState(State s);
    void setRendered(bool);
    bool isRendered(void) const;

    Player(unsigned int, unsigned int, unsigned int, unsigned int l, unsigned int o, const  char *, unsigned int,  State i);
    ~Player();
    Player& operator=(Player&);
  };

}
#endif
