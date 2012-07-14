/*
** OPlayers.h
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Wed Jun 29 19:44:02 2011 Sabmit
** $Id$
**
** Author(s):
**  - Sabmit <>
**
** Copyright (C) 2011 Sabmit
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#ifndef   	PLAYERSMANAGER_H_
# define   	PLAYERSMANAGER_H_

#include <utility>
#include "OgreMain.h"
#include "Player.hh"

class           PlayersManager
{
  class OPlayer
  {
  private:
    Ogre::Entity *mEnt;
    Ogre::SceneNode *mSceneNode;
    Ogre::Vector3 mDir;
    Ogre::Real mDist;
    zappy::State oldState;
    zappy::State newState;
    Ogre::ParticleSystem *Spell;
    Ogre::ParticleSystem *Broad;
    bool isAttached;

  public:
    OPlayer(Ogre::Entity *, Ogre::SceneNode *);
    ~OPlayer(void);

  public:
    Ogre::Entity *getEntity(void) const;
    Ogre::SceneNode *getSceneNode(void) const;
    Ogre::Vector3 &getDirection(void);
    Ogre::Real &getDistance(void);

  public:
    void setDirection(Ogre::Vector3 &dest);
    void setDistance(Ogre::Real &dist);
    bool stateHasChanged(void) const;
    void setSpell(Ogre::ParticleSystem *s) {this->Spell = s;}
    void setBroad(Ogre::ParticleSystem *b) {this->Broad = b;}
    void updateState(zappy::State);
    void attachSpell(void);
    void attachBroad(void);
    void detachAnim(void);
  };

typedef bool (PlayersManager::*fptr)(zappy::Player *, int i);

private:
  Ogre::SceneManager *mSceneMgr;
  std::vector<OPlayer *> mOPlayers;
  std::list<zappy::Player *> *mPlayers;
  std::map<zappy::State, fptr> updatePlayer;
  Ogre::Real speed;
  Ogre::Real tslf;
  Ogre::Real time;

public:
  PlayersManager(void);
  ~PlayersManager(void);

public:
  void initialize(std::list<zappy::Player*> *players, Ogre::SceneManager *sm, unsigned int time);
  void update(const Ogre::FrameEvent &evt);
  void clear(void);

private:
  void createPlayer(zappy::Player *player);
  bool moving(zappy::Player *, int i);
  bool forking(zappy::Player *p, int i);
  bool expulsing(zappy::Player *p, int i);
  bool broadcasting(zappy::Player *p, int i);
  bool taking(zappy::Player *p, int i);
  bool dropping(zappy::Player *p, int i);
  bool hidle(zappy::Player *p, int i);
  bool dying(zappy::Player *p, int i);
  bool begSpelling(zappy::Player *p, int i);
  bool endSpelling(zappy::Player *p, int i);
};

#endif 	    /* !PLAYERSMANAGER_H_ */
