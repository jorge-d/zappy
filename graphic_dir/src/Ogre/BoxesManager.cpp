/*
** BoxesManager.cpp
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Thu Jul  7 21:52:10 2011 Sabmit
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
#include <functional>
#include "Constants.h"
#include "BoxesManager.h"
#include "RessourceFactory.h"

BoxesManager::BoxesManager(void)
{
}

BoxesManager::~BoxesManager(void)
{
  this->clear();
}

void
BoxesManager::clear(void)
{
  if (this->mRessources.size() > 0)
    {
      std::vector<std::map<zappy::Elements, ORessource *> >::iterator it;
      for (it = this->mRessources.begin(); it != this->mRessources.end(); ++it)
        {
          for (int i = 0; i < Constants::nbElem; ++i)
            {
              zappy::Elements type = static_cast<zappy::Elements>(i);
              std::map<zappy::Elements, ORessource *>::iterator itFind;

              itFind = (*it).find(type);
              if (itFind != (*it).end())
                delete ((*it)[type]);
            }
        }
      this->mRessources.clear();
    }
}

BoxesManager::ORessource *
BoxesManager::createRessource(zappy::Elements type, unsigned int x, unsigned  int y)
{
  return this->mFactory->build(type, x, y);
}

void
BoxesManager::updateBox(zappy::Box *box, unsigned int idx)
{
  std::map<zappy::Elements, ORessource *>::iterator itFind;
  std::map<zappy::Elements, ORessource *> &toUp = this->mRessources.at(idx);
  unsigned int *elem;
  zappy::Elements type;
  unsigned int x;
  unsigned int y;

  std::cout << "a" << std::endl;
  elem = box->getElements();
  for (int i = 0; i < Constants::nbElem; ++i)
    {
  std::cout << "b" << std::endl;
      x = box->getX();
      y = box->getY();
      type = static_cast<zappy::Elements>(i);
      if (elem[i] > 0)
        {
          if (toUp.count(type) > 0)
            toUp[type]->show();
          else
            toUp[type] = this->createRessource(type, x, y);
        }
      else
        {
  std::cout << "d" << std::endl;
          if (toUp.count(type))
            toUp[type]->hide();
        }
    }
}

void
BoxesManager::initBox(zappy::Box *box)
{
  std::map<zappy::Elements, ORessource *> toAdd;
  unsigned int *elem;
  zappy::Elements type;
  unsigned int x;
  unsigned int y;

  elem = box->getElements();
  for (int i = 0; i < Constants::nbElem; ++i)
    {
      x = box->getX();
      y = box->getY();
      type = static_cast<zappy::Elements>(i);
      if (elem[i] > 0)
        toAdd[type] = this->createRessource(type, x, y);
    }
  this->mRessources.push_back(toAdd);

}

void
BoxesManager::update(std::list<unsigned int> &listIdx)
{
  std::list<unsigned int>::iterator it;

  for (it = listIdx.begin(); it != listIdx.end(); ++it)
    this->updateBox(this->mBoxes->at(*it), *it);
}

void
BoxesManager::initialize(std::vector<zappy::Box*> *boxes, Ogre::SceneManager *sm)
{
  this->mBoxes = boxes;
  this->mSceneManager = sm;
  this->mFactory = new RessourceFactory(this->mSceneManager);
  std::for_each(this->mBoxes->begin(),
                this->mBoxes->end(),
                std::bind1st(std::mem_fun(&BoxesManager::initBox), this));
}
