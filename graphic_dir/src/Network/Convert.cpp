#include <iostream>
#include <cstdio>
#include <cstring>
#include "Convert.hh"
#include "Grid.hh"
#include "Network.hh"

namespace zappy
{
  Convert::Convert(): _endMap(true)
  {
    _p_tab["msz"] = &Convert::getMapSize;
    _p_tab["sgt"] = &Convert::getTimeUnit;
    _p_tab["bct"] = &Convert::getMapBox;
    _p_tab["tna"] = &Convert::getTeamNames;
    _p_tab["pnw"] = &Convert::getPlayer;
    _p_tab["enw"] = &Convert::getEgg;
    _p_tab["ebo"] = &Convert::getPlayerFromEgg;
    _p_tab["ppo"] = &Convert::getPlayerPosition;
    _p_tab["pgt"] = &Convert::getPlayerTake;
    _p_tab["pdr"] = &Convert::getPlayerDrop;
    _p_tab["pin"] = &Convert::getPlayerBag;
    _p_tab["pex"] = &Convert::getPlayerEx;
    _p_tab["pbc"] = &Convert::getPlayerBroadcast;
    _p_tab["pic"] = &Convert::getPlayerSpellBegin;
    _p_tab["plv"] = &Convert::getPlayerLevel;
    _p_tab["pfk"] = &Convert::getPlayerFork;
    _p_tab["eht"] = &Convert::getEggHatch;
    _p_tab["edi"] = &Convert::getEggDeath;
    _p_tab["pdi"] = &Convert::getPlayerDeath;
    _p_tab["seg"] = &Convert::getGameOver;
  }

  Convert::~Convert()
  {
    ;
  }


  void Convert::setMap(std::string &s)
  {
    try
      {
	std::map<std::string, Convert::ptr>::iterator it= _p_tab.begin();
	std::string key;
	std::string str;
	std::string w;

	key = s.substr(0, s.find_first_of(' '));
	w = s.substr(0, 9);
	if (w.compare("BIENVENUE") == 0)
	  {
	    std::cout << ">> BIENVENUE" << std::endl;
	    bienvenue();
	  }
	else if ((it = _p_tab.find(key)) != _p_tab.end()) {
	  s = s.substr(s.find_first_of(' ') + 1);
	  (this->*(it->second))(s);
	}
      }
    catch (std::exception &)
      {
	std::cout << "Server disconnected\n";
      }
  }

  void Convert::bienvenue()
  {
    Network::getInstance().setToSend("GRAPHIC\n");
    std::cout << "<< GRAPHIC" <<std::endl;
  }

  void Convert::getPlayerLevel(std::string &s)
  {
    unsigned int n = 0;
    unsigned int l = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d %d", &n, &l)) == 2)
      Grid::getInstance().setPlayerLevel(n,l);
  }

  void Convert::getMapSize(std::string &s)
  {
    unsigned int x = 0, y = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d %d", &x, &y)) == 2)
      Grid::getInstance().setMapSize(x,y);
  }

  void Convert::getTimeUnit(std::string &s)
  {
    unsigned int t = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d", &t)) == 1)
      Grid::getInstance().setTimeUnit(t);
  }

  void Convert::getMapBox(std::string &s)
  {
    unsigned int x = 0, y = 0;
    unsigned int i[7];
    int is = 0;

    bzero(i, sizeof(int) * 7);
    if ((is = sscanf(s.c_str(), "%d %d %d %d %d %d %d %d %d", &x, &y, &i[0], &i[1], &i[2], &i[3], &i[4], &i[5], &i[6])) == 9)
      Grid::getInstance().setGrid(x,y,i);
  }

  void Convert::getTeamNames(std::string &s)
  {
    _endMap = false;
    Grid::getInstance().addTeamNames(s);
  }

  bool Convert::getEndMap() const
  {
    return _endMap;
  }

  void Convert::getPlayer(std::string &s)
  {
    unsigned int x = 0, y = 0 , l = 0, o = 0, id = 0, tid = 0;
    char str[1024];
    int i = 0;

    bzero(str, 1024);
    if ((i = sscanf(s.c_str(), "%d %d %d %d %d %s", &id, &x, &y, &o, &l, str)) == 6)
      {
	tid = Grid::getInstance().getIdFromName(str);
	Player *p = new Player(id, x, y, l, o, str, tid, IDLE);
	Grid::getInstance().addPlayer(*p);
      }
  }

  void Convert::getEgg(std::string &s)
  {
    unsigned int x = 0, y = 0,  n =0;
    unsigned int  id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d %d %d %d", &id, &n, &x, &y)) == 4)
      {
	Egg *e = new Egg(id, n, x, y);
	Grid::getInstance().addEgg(*e);
      }
  }

  void Convert::getPlayerFromEgg(std::string &s)
  {
    unsigned int id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d", &id)) == 1)
      Grid::getInstance().setEggState(id, true);
  }

  void Convert::getPlayerPosition(std::string &s)
  {
    unsigned int x = 0, y = 0, o = 0;
    unsigned int  id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d %d %d %d", &id, &x, &y, &o)) == 4)
      {
	Grid::getInstance().setPlayerPosition(x, y, id, o);
	Grid::getInstance().setPlayerState(id, MOVING);
      }
  }

  void Convert::getPlayerTake(std::string &s)
  {
    unsigned int x = 0;
    unsigned int  id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d %d", &id, &x)) == 2)
      {
	Grid::getInstance().setPlayerTBag(id, static_cast<Elements>(x));
	Grid::getInstance().setPlayerState(id, TAKING);
      }
  }

  void Convert::getPlayerDrop(std::string &s)
  {
    unsigned int x = 0;
    unsigned int  id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d %d", &id, &x)) == 2)
      {
	Grid::getInstance().setPlayerFBag(id, static_cast<Elements>(x));
	Grid::getInstance().setPlayerState(id, DROPPING);
      }
  }

  void Convert::getPlayerEx(std::string &s)
  {
    unsigned int id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d", &id)) == 1)
      Grid::getInstance().setPlayerState(id, EXPULSING);
  }

  void Convert::getPlayerBag(std::string &s)
  {
    unsigned int x = 0, y = 0;
    unsigned int i[7];
    unsigned int id = 0;
    int is = 0;

    bzero(i, sizeof(int) * 7);
    if ((is = sscanf(s.c_str(), "%d %d %d %d %d %d %d %d %d %d", &id, &x, &y, &i[0], &i[1], &i[2], &i[3], &i[4], &i[5], &i[6])) == 10)
      Grid::getInstance().setPlayerBag(x,y,id,i);
  }

  void Convert::getPlayerSpellBegin(std::string &s)
  {
    std::stringstream ss(s);
    unsigned int x = 0, y = 0;
    unsigned int id = 0, l = 0;

    ss >> x;
    ss >> y;
    ss >> l;
    do {
      ss >> id;
      Grid::getInstance().setPlayerState(id, BEG_SPELLING);
    } while (ss.good());
  }

  void Convert::getPlayerBroadcast(std::string &s)
  {
    unsigned int id = 0;
    char ms[1024];
    int i = 0;

    bzero(ms, 1024);
    if ((i = sscanf(s.c_str(), "%d %s", &id, ms)) == 2)
      {
	Grid::getInstance().setPlayerMessage(id, ms);
	Grid::getInstance().setPlayerState(id, BROADCASTING);
      }
  }

  void Convert::getPlayerFork(std::string &s)
  {
    unsigned int id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d", &id)) == 1)
      Grid::getInstance().setPlayerState(id, FORKING);
  }

  void Convert::getEggHatch(std::string &s)
  {
    unsigned int id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d", &id)) == 1)
      Grid::getInstance().setEggState(id, true);
  }

  void Convert::getEggDeath(std::string &s)
  {
    unsigned int id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d", &id)) == 1)
      Grid::getInstance().setEggState(id, false);

  }

  void Convert::getPlayerDeath(std::string &s)
  {
    unsigned int id = 0;
    int i = 0;

    if ((i = sscanf(s.c_str(), "%d", &id)) == 1)
      Grid::getInstance().setPlayerState(id, DYING);
  }

  void Convert::getGameOver(std::string &s)
  {
    Grid::getInstance().setWinners(s);
  }

}
