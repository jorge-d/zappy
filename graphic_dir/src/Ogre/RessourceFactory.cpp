/*
** RessourceFactory.cpp
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Sat Jul  9 02:20:09 2011 Sabmit
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
#include "Constants.h"
#include "Tools.h"
#include "BoxesManager.h"
#include "RessourceFactory.h"

RessourceFactory::RessourceFactory(Ogre::SceneManager *sm) :
  mSceneMgr(sm)
{
  this->mBuilder[zappy::LINEMATE] = &RessourceFactory::buildL;
  this->mBuilder[zappy::DERAUMERE] = &RessourceFactory::buildD;
  this->mBuilder[zappy::SIBUR] = &RessourceFactory::buildS;
  this->mBuilder[zappy::MENDIANE] = &RessourceFactory::buildM;
  this->mBuilder[zappy::PHIRAS] = &RessourceFactory::buildP;
  this->mBuilder[zappy::THYSTAME] = &RessourceFactory::buildT;
  this->mBuilder[zappy::FOOD] = &RessourceFactory::buildF;
}

RessourceFactory::~RessourceFactory(void)
{

}

BoxesManager::ORessource *
RessourceFactory::build(zappy::Elements type, unsigned int x, unsigned int y)
{
  std::map<zappy::Elements, RessourceFactory::builder>::iterator it;

  it = this->mBuilder.find(type);
  if (it != this->mBuilder.end())
    {
      builder toBuild = (*it).second;
      return (this->*toBuild)(x, y);
    }
  return NULL;
}

BoxesManager::ORessource *
RessourceFactory::buildL(unsigned int x, unsigned int y)
{
  std::string id(NumberToString(x) + " " + NumberToString(y));
  Ogre::Entity *ent = NULL;
  Ogre::SceneNode *node = NULL;
  unsigned int xReal;
  unsigned int yReal;
  int randNb;

  srand(1 * x * y);
  randNb = rand() % 100;
  xReal = x * Constants::SquareSize + randNb;
  yReal = y * Constants::SquareSize + randNb;
  ent = this->mSceneMgr->createEntity("pierre_bleue.mesh");
  ent->setMaterialName("stoneB");
  node = this->mSceneMgr->getRootSceneNode()->
    createChildSceneNode("nodeL" + id, Ogre::Vector3(xReal, 0, yReal));
  node->setScale(Constants::Scale, Constants::Scale, Constants::Scale);
  node->attachObject(ent);
  return (new BoxesManager::ORessource(ent, node));
}

BoxesManager::ORessource *
RessourceFactory::buildD(unsigned int x, unsigned int y)
{
  std::string id(NumberToString(x) + " " + NumberToString(y));
  Ogre::Entity *ent = NULL;
  Ogre::SceneNode *node = NULL;
  unsigned int xReal;
  unsigned int yReal;
  int randNb;

  srand(2 * x * y);
  randNb = rand() % 100;
  xReal = x * Constants::SquareSize + randNb;
  yReal = y * Constants::SquareSize + randNb;
  ent = this->mSceneMgr->createEntity("pierre_fushia.mesh");
  ent->setMaterialName("stoneF");
  node = this->mSceneMgr->getRootSceneNode()->
    createChildSceneNode("nodeD" + id, Ogre::Vector3(xReal, 0, yReal));
  node->setScale(Constants::Scale, Constants::Scale, Constants::Scale);
  node->attachObject(ent);
  return (new BoxesManager::ORessource(ent, node));
}

BoxesManager::ORessource *
RessourceFactory::buildS(unsigned int x, unsigned int y)
{
  std::string id(NumberToString(x) + " " + NumberToString(y));
  Ogre::Entity *ent = NULL;
  Ogre::SceneNode *node = NULL;
  unsigned int xReal;
  unsigned int yReal;
  int randNb;

  srand(3 * x * y);
  randNb = rand() % 100;
  xReal = x * Constants::SquareSize + randNb;
  yReal = y * Constants::SquareSize + randNb;
  ent = this->mSceneMgr->createEntity("pierre_jaune.mesh");
  ent->setMaterialName("stoneJ");
  node = this->mSceneMgr->getRootSceneNode()->
    createChildSceneNode("nodeS" + id, Ogre::Vector3(xReal, 0, yReal));
  node->setScale(Constants::Scale, Constants::Scale, Constants::Scale);
  node->attachObject(ent);
  return (new BoxesManager::ORessource(ent, node));
}

BoxesManager::ORessource *
RessourceFactory::buildM(unsigned int x, unsigned int y)
{
  std::string id(NumberToString(x) + " " + NumberToString(y));
  Ogre::Entity *ent = NULL;
  Ogre::SceneNode *node = NULL;
  unsigned int xReal;
  unsigned int yReal;
  int randNb;

  srand(4 * x * y);
  randNb = rand() % 100;
  xReal = x * Constants::SquareSize + randNb;
  yReal = y * Constants::SquareSize + randNb;
  ent = this->mSceneMgr->createEntity("pierre_orange.mesh");
  ent->setMaterialName("stoneO");
  node = this->mSceneMgr->getRootSceneNode()->
    createChildSceneNode("nodeM" + id, Ogre::Vector3(xReal, 0, yReal));
  node->setScale(Constants::Scale, Constants::Scale, Constants::Scale);
  node->attachObject(ent);
  return (new BoxesManager::ORessource(ent, node));
}

BoxesManager::ORessource *
RessourceFactory::buildP(unsigned int x, unsigned int y)
{
  std::string id(NumberToString(x) + " " + NumberToString(y));
  Ogre::Entity *ent = NULL;
  Ogre::SceneNode *node = NULL;
  unsigned int xReal;
  unsigned int yReal;
  int randNb;

  srand(5 * x * y);
  randNb = rand() % 100;
  xReal = x * Constants::SquareSize + randNb;
  yReal = y * Constants::SquareSize + randNb;
  ent = this->mSceneMgr->createEntity("pierre_rouge.mesh");
  ent->setMaterialName("stoneR");
  node = this->mSceneMgr->getRootSceneNode()->
    createChildSceneNode("nodeP" + id, Ogre::Vector3(xReal, 0, yReal));
  node->setScale(Constants::Scale, Constants::Scale, Constants::Scale);
  node->attachObject(ent);
  return (new BoxesManager::ORessource(ent, node));
}

BoxesManager::ORessource *
RessourceFactory::buildT(unsigned int x, unsigned int y)
{
  std::string id(NumberToString(x) + " " + NumberToString(y));
  Ogre::Entity *ent = NULL;
  Ogre::SceneNode *node = NULL;
  unsigned int xReal;
  unsigned int yReal;
  int randNb;

  srand(6 * x * y);
  randNb = rand() % 100;
  xReal = x * Constants::SquareSize + randNb;
  yReal = y * Constants::SquareSize + randNb;
  ent = this->mSceneMgr->createEntity("pierre_verte.mesh");
  ent->setMaterialName("stoneV");
  node = this->mSceneMgr->getRootSceneNode()->
    createChildSceneNode("nodeT" + id, Ogre::Vector3(xReal, 0, yReal));
  node->setScale(Constants::Scale, Constants::Scale, Constants::Scale);
  node->attachObject(ent);
  return (new BoxesManager::ORessource(ent, node));
}

BoxesManager::ORessource *
RessourceFactory::buildF(unsigned int x, unsigned int y)
{
  return NULL;
}
