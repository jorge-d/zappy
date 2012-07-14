/*
** BoxesManager.h
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Thu Jul  7 21:52:26 2011 Sabmit
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

#ifndef   	BOXESMANAGER_H_
# define   	BOXESMANAGER_H_

#include <vector>
#include <utility>
#include "OgreMain.h"
#include "Box.hh"

class           RessourceFactory;
class           BoxesManager
{
public:
  class         ORessource
  {
  private:
    Ogre::Entity  *mEnt;
    Ogre::SceneNode *mSceneNode;

  public:
    ORessource(Ogre::Entity *, Ogre::SceneNode *);
    ~ORessource(void);

  public:
    Ogre::SceneNode *getSceneNode(void);
    Ogre::Entity *getEntity(void);
    void show(void);
    void hide(void);
  };

private:
  std::vector<std::map<zappy::Elements, ORessource *> > mRessources;
  std::vector<zappy::Box*> *mBoxes;
  Ogre::SceneManager *mSceneManager;
  RessourceFactory *mFactory;

public:
  BoxesManager(void);
  ~BoxesManager(void);

public:
  void initialize(std::vector<zappy::Box*>*, Ogre::SceneManager *);
  ORessource *createRessource(zappy::Elements type, unsigned int x, unsigned int y);
  void initBox(zappy::Box *);
  void updateBox(zappy::Box *box, unsigned int idx);
  void update(std::list<unsigned int> &listIdx);
  void clear(void);
};

#endif 	    /* !BOXESMANAGER_H_ */
