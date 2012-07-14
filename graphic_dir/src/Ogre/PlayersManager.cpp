/*
** OPlayer.cpp
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Wed Jun 29 19:50:02 2011 Sabmit
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

#include <iostream>
#include <utility>
#include "PlayersManager.h"
#include "Constants.h"
#include "OgreMain.h"
#include "Player.hh"
#include "Tools.h"

PlayersManager::PlayersManager()
{
}

//-------------------------------------------------------------------------------------
PlayersManager::~PlayersManager(void)
{
  this->clear();
}

//-------------------------------------------------------------------------------------
void
PlayersManager::initialize(std::list<zappy::Player*> *players, Ogre::SceneManager *sm, unsigned int time)
{
  Ogre::ParticleSystem::setDefaultNonVisibleUpdateTimeout(5);

  this->mPlayers = players;
  this->mSceneMgr = sm;
  this->time = time;
  this->updatePlayer[zappy::MOVING] = &PlayersManager::moving;
  this->updatePlayer[zappy::FORKING] = &PlayersManager::forking;
  this->updatePlayer[zappy::EXPULSING] = &PlayersManager::expulsing;
  this->updatePlayer[zappy::BROADCASTING] = &PlayersManager::broadcasting;
  this->updatePlayer[zappy::TAKING] = &PlayersManager::taking;
  this->updatePlayer[zappy::DROPPING] = &PlayersManager::dropping;
  this->updatePlayer[zappy::IDLE] = &PlayersManager::hidle;
  this->updatePlayer[zappy::DYING] = &PlayersManager::dying;
  this->updatePlayer[zappy::BEG_SPELLING] = &PlayersManager::begSpelling;
  this->updatePlayer[zappy::END_SPELLING] = &PlayersManager::endSpelling;
}

void
PlayersManager::clear(void)
{
  std::vector<OPlayer *>::iterator it;

  if (this->mOPlayers.size() > 0)
    {
      for (it = this->mOPlayers.begin(); it != this->mOPlayers.end(); ++it)
        delete (*it);
      this->mOPlayers.clear();
    }
}

void
PlayersManager::createPlayer(zappy::Player *player)
{
  Ogre::Entity *ent;
  Ogre::SceneNode *node;
  Ogre::AnimationState *anim;
  std::string id(NumberToString<unsigned int>(player->getId()));
  OPlayer *toAdd;

  ent = this->mSceneMgr->createEntity("Player" + id, "robot.mesh");
  node = this->mSceneMgr->getRootSceneNode()->
    createChildSceneNode(PLAYERNODENAME + id,
                         Ogre::Vector3(player->getX() * Constants::SquareSize,
                                       0,
                                       player->getY() * Constants::SquareSize));
  ent->setQueryFlags(Constants::PLAYER_MASK);
  anim = ent->getAnimationState("Idle");
  anim->setLoop(true);
  anim->setEnabled(true);
  node->attachObject(ent);
  player->setRendered(true);
  toAdd = new OPlayer(ent, node);
  toAdd->setSpell(this->mSceneMgr->createParticleSystem("Aureola" + id, "Examples/Aureola"));
  toAdd->setBroad(this->mSceneMgr->createParticleSystem("Purple" + id, "Examples/PurpleFountain"));
  this->mOPlayers.push_back(toAdd);
}

//-------------------------------------------------------------------------------------
void
PlayersManager::update(const Ogre::FrameEvent &evt)
{
  std::list<zappy::Player*>::iterator it = this->mPlayers->begin();

  this->tslf = evt.timeSinceLastFrame;
  for (int i = 0; it != this->mPlayers->end(); ++i, ++it)
    {
      if (!(*it)->isRendered())
        this->createPlayer(*it);
      this->mOPlayers.at(i)->updateState((*it)->getState());
      (this->*updatePlayer[(*it)->getState()])(*it, i);
    }
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::moving(zappy::Player *p, int i)
{
  OPlayer *OPlayer = this->mOPlayers.at(i);
  this->speed = Constants::SquareSize /
    ((Constants::timeUnit / static_cast<Ogre::Real>(time)));

  Ogre::SceneNode *node = OPlayer->getSceneNode();
  Ogre::Vector3 &direction = OPlayer->getDirection();
  Ogre::Real &distance = OPlayer->getDistance();
  Ogre::Real move = this->speed * this->tslf;
  Ogre::Vector3 destination(p->getX() * Constants::SquareSize, 0, p->getY() * Constants::SquareSize);
  Ogre::AnimationState *anim = OPlayer->getEntity()->
    getAnimationState(distance <= 0.0f ? "Idle" : "Walk");

  anim->setLoop(true);
  anim->setEnabled(true);
  if (direction == Ogre::Vector3::ZERO)
    {
      Ogre::Vector3 src = node->getOrientation() * Ogre::Vector3::UNIT_X;
      direction = destination - node->getPosition();
      distance = direction.normalise();
      if ((1.0f + src.dotProduct(direction)) < 0.0001f)
        node->yaw(Ogre::Degree(180));
      else
        node->rotate(src.getRotationTo(direction));
      if (distance > Constants::SquareSize)
        distance = 0.0f;
    }
  else
    {
      distance -= move;
      if (distance <= 0.0f)
        {
          node->setPosition(destination);
          direction = Ogre::Vector3::ZERO;
        }
      else
        node->translate(direction * move);
    }
  if (OPlayer->stateHasChanged())
    OPlayer->detachAnim();
  anim->addTime(this->tslf);
  return true;
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::begSpelling(zappy::Player *p, int i)
{
  (void)p;
  OPlayer *OPlayer;

  OPlayer = this->mOPlayers.at(i);
  if (OPlayer->stateHasChanged())
    OPlayer->attachSpell();
  return true;
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::endSpelling(zappy::Player *p, int i)
{
  (void)p;
  OPlayer *OPlayer;

  OPlayer = this->mOPlayers.at(i);
  if (OPlayer->stateHasChanged())
    OPlayer->detachAnim();
  return true;
}


//-------------------------------------------------------------------------------------
bool
PlayersManager::forking(zappy::Player *p, int i)
{
  OPlayer *OPlayer = this->mOPlayers.at(i);

  if (OPlayer->stateHasChanged())
    OPlayer->detachAnim();
  return true;
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::expulsing(zappy::Player *p, int i)
{
  OPlayer *OPlayer = this->mOPlayers.at(i);

  if (OPlayer->stateHasChanged())
    OPlayer->detachAnim();
  return true;
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::broadcasting(zappy::Player *p, int i)
{
  (void)p;
  OPlayer *OPlayer;

  OPlayer = this->mOPlayers.at(i);
  if (OPlayer->stateHasChanged())
    OPlayer->attachBroad();
  return true;
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::taking(zappy::Player *p, int i)
{
  OPlayer *OPlayer;

  OPlayer = this->mOPlayers.at(i);
  Ogre::AnimationState *anim = OPlayer->getEntity()->
    getAnimationState("Slump");
  anim->setEnabled(true);
  anim->setLoop(true);
  anim->addTime(this->tslf);
  if (OPlayer->stateHasChanged())
    OPlayer->detachAnim();
  return true;
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::dropping(zappy::Player *p, int i)
{
  OPlayer *OPlayer = this->mOPlayers.at(i);

  if (OPlayer->stateHasChanged())
    OPlayer->detachAnim();
  return true;
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::hidle(zappy::Player *p, int i)
{
  OPlayer *OPlayer = this->mOPlayers.at(i);

  if (OPlayer->stateHasChanged())
    OPlayer->detachAnim();
  Ogre::Vector3 position(p->getX() * Constants::SquareSize, 0, p->getY() * Constants::SquareSize);
  Ogre::AnimationState *anim = OPlayer->getEntity()->
    getAnimationState("Idle");
  Ogre::SceneNode *node = OPlayer->getSceneNode();
  anim->setEnabled(true);
  if (position != node->getPosition())
      node->setPosition(position);
  anim->setLoop(true);
  anim->setEnabled(true);
  anim->addTime(this->tslf);
  return true;
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::dying(zappy::Player *p, int i)
{
  OPlayer *OPlayer = this->mOPlayers.at(i);

  if (OPlayer->stateHasChanged())
    OPlayer->detachAnim();
  Ogre::Vector3 position(p->getX() * Constants::SquareSize, 0, p->getY() * Constants::SquareSize);
  Ogre::AnimationState *anim = OPlayer->getEntity()->
    getAnimationState("Die");
  Ogre::SceneNode *node = OPlayer->getSceneNode();
  if (position != node->getPosition())
      node->setPosition(position);
  anim->setEnabled(true);
  anim->setLoop(false);
  anim->addTime(this->tslf);
  return true;
}
