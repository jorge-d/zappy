#ifndef _CONVERT_H
# define _CONVERT_H

#include <string>
#include <map>


namespace zappy
{

  class Convert
  {
  public:
    typedef void (Convert::*ptr)(std::string &);

  private:

    std::map<std::string,Convert::ptr> _p_tab;
    bool _endMap;

    void bienvenue();
    void getMapSize(std::string &);
    void getMapBox(std::string &);

    void getTeamNames(std::string &);
    void getTimeUnit(std::string &);

    void getPlayer(std::string &);
    void getEgg(std::string &);
    void getPlayerFromEgg(std::string &);

    void getPlayerPosition(std::string &);
    void getPlayerEx(std::string &);
    void getPlayerTake(std::string &);
    void getPlayerDrop(std::string &);
    void getPlayerMove(std::string &);
    void getPlayerBag(std::string &);
    void getPlayerLevel(std::string &);

    void getPlayerSpellBegin(std::string &);
    void getPlayerSpellEnd(std::string &);
    void getPlayerBroadcast(std::string &);

    void getPlayerFork(std::string &);

    void getEggHatch(std::string &);

    void getEggDeath(std::string &);
    void getPlayerDeath(std::string &);
    void getGameOver(std::string &);

  public:
    Convert();
    ~Convert();
    void setMap(std::string &);
    bool getEndMap() const;
  };

}

#endif
