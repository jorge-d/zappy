/*
** ORessource.cpp
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Fri Jul  8 22:43:48 2011 Sabmit
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
#include "BoxesManager.h"

BoxesManager::ORessource::ORessource(Ogre::Entity *ent, Ogre::SceneNode *node) :
  mEnt(ent), mSceneNode(node)
{
}

BoxesManager::ORessource::~ORessource(void)
{
  // delete this->mEnt;
  // delete this->mSceneNode;
}

Ogre::SceneNode *
BoxesManager::ORessource::getSceneNode(void)
{
  return this->mSceneNode;
}

Ogre::Entity *
BoxesManager::ORessource::getEntity(void)
{
  return this->mEnt;
}

void
BoxesManager::ORessource::show(void)
{
  std::cout << "SHOW" << std::endl;
  if (this->mSceneNode && this->mEnt)
    {
      this->mSceneNode->setVisible(true);
      this->mEnt->setVisible(true);
    }
  std::cout << "END SHOW" << std::endl;
}

void
BoxesManager::ORessource::hide(void)
{
  std::cout << "HIDE" << std::endl;
  this->mSceneNode->setVisible(false);
  this->mEnt->setVisible(false);
}
