/*
** OPlayer.cpp
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Thu Jun 30 21:26:59 2011 Sabmit
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
#include <OgreIteratorWrapper.h>
#include "OgreMain.h"
#include "PlayersManager.h"

PlayersManager::OPlayer::OPlayer(Ogre::Entity *ent, Ogre::SceneNode *sn) :
  mEnt(ent), mSceneNode(sn), mDir(Ogre::Vector3::ZERO), mDist(0.0f),
  oldState(zappy::NONE), newState(zappy::NONE), isAttached(false)
{
}

//-------------------------------------------------------------------------------------
PlayersManager::OPlayer::~OPlayer(void)
{
  // delete this->Spell;
  // delete this->mEnt;
  // delete this->mSceneNode;
}

//-------------------------------------------------------------------------------------
Ogre::Entity *
PlayersManager::OPlayer::getEntity(void) const
{
  return this->mEnt;
}

//-------------------------------------------------------------------------------------
Ogre::SceneNode *
PlayersManager::OPlayer::getSceneNode(void) const
{
  return this->mSceneNode;
}

//-------------------------------------------------------------------------------------
Ogre::Vector3 &
PlayersManager::OPlayer::getDirection(void)
{
  return this->mDir;
}

//-------------------------------------------------------------------------------------
Ogre::Real &
PlayersManager::OPlayer::getDistance(void)
{
  return this->mDist;
}

//-------------------------------------------------------------------------------------
void
PlayersManager::OPlayer::setDirection(Ogre::Vector3 &dir)
{
  this->mDir = dir;
}

//-------------------------------------------------------------------------------------
void
PlayersManager::OPlayer::setDistance(Ogre::Real &dist)
{
  this->mDist = dist;
}

//-------------------------------------------------------------------------------------
bool
PlayersManager::OPlayer::stateHasChanged() const
{
  if (this->oldState != this->newState)
    return true;
  return false;
}

//-------------------------------------------------------------------------------------
void
PlayersManager::OPlayer::updateState(zappy::State state)
{
  this->oldState = this->newState;
  this->newState = state;
}

//-------------------------------------------------------------------------------------
void
PlayersManager::OPlayer::attachBroad(void)
{
  if (this->isAttached == false)
    {
      this->Spell->clear();
      this->Broad->clear();
      this->mSceneNode->attachObject(this->Broad);
      this->isAttached = true;
    }
}

//-------------------------------------------------------------------------------------
void
PlayersManager::OPlayer::attachSpell(void)
{
  if (this->isAttached == false)
    {
      this->Spell->clear();
      this->Broad->clear();
      this->mSceneNode->attachObject(this->Spell);
      this->isAttached = true;
    }
}

//-------------------------------------------------------------------------------------
void
PlayersManager::OPlayer::detachAnim(void)
{
  if (this->isAttached)
    {
      this->Spell->clear();
      this->Broad->clear();
      this->mSceneNode->detachObject(this->Spell);
      this->mSceneNode->detachObject(this->Broad);
      this->isAttached = false;
    }
}
