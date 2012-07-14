/*
** NetworkManager.h
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Fri Jun 17 17:58:32 2011 Sabmit
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

#ifndef   	NETWORKMANAGER_H_
# define   	NETWORKMANAGER_H_

#include <string>
#include "CEGUIMain.h"
#include "Constants.h"
#include "Tools.h"

class           GraphicsManager;

class           NetworkManager
{
protected:
  std::map<Constants::Selected,std::string *> mSelected;
  GraphicsManager* GfxMgr_;
  std::string ip_;
  int port_;

public:
  NetworkManager(GraphicsManager* GfxMgr);
  ~NetworkManager(void);

public:
  bool  connect(const CEGUI::EventArgs&);
  bool  isConnected(void);
  void  updateBox(unsigned int, unsigned int);
  void  updateBag(unsigned int);
  bool  updateTime(const CEGUI::EventArgs&);
  void  update(void);
  void  set(Constants::Selected elem, std::string &);
  void  unset(Constants::Selected elem);
};

#endif 	    /* !NETWORKMANAGER_H_ */
