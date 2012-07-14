/*
** RessourceFactory.h
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Sat Jul  9 02:10:48 2011 Sabmit
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

#ifndef   	RESSOURCEFACTORY_H_
# define   	RESSOURCEFACTORY_H_

#include <map>
#include "Box.hh"
#include "OgreMain.h"
#include "BoxesManager.h"

class           RessourceFactory
{
private:
  typedef BoxesManager::ORessource* (RessourceFactory::*builder)(unsigned int x, unsigned int y);
  std::map<zappy::Elements, builder> mBuilder;
  Ogre::SceneManager *mSceneMgr;

public:
  RessourceFactory(Ogre::SceneManager *);
  ~RessourceFactory(void);

public:
  BoxesManager::ORessource *build(zappy::Elements, unsigned int x, unsigned int y);

private:
  BoxesManager::ORessource *buildL(unsigned int x, unsigned int y);
  BoxesManager::ORessource *buildD(unsigned int x, unsigned int y);
  BoxesManager::ORessource *buildS(unsigned int x, unsigned int y);
  BoxesManager::ORessource *buildM(unsigned int x, unsigned int y);
  BoxesManager::ORessource *buildP(unsigned int x, unsigned int y);
  BoxesManager::ORessource *buildT(unsigned int x, unsigned int y);
  BoxesManager::ORessource *buildF(unsigned int x, unsigned int y);
};

#endif 	    /* !RESSOURCEFACTORY_H_ */
