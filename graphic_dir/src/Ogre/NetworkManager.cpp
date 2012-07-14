/*
** NetworkManager.cpp
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Fri Jun 17 17:54:38 2011 Sabmit
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
#include "GraphicsManager.h"
#include "NetworkManager.h"
#include "Network.hh"
#include "Thread.hpp"

NetworkManager::NetworkManager(GraphicsManager* GfxMgr) :
  GfxMgr_(GfxMgr), ip_(""), port_(0)
{
}

//-------------------------------------------------------------------------------------
NetworkManager::~NetworkManager(void)
{
}

//-------------------------------------------------------------------------------------
bool
NetworkManager::connect(const CEGUI::EventArgs&)
{
  CEGUI::WindowManager *winMgr = CEGUI::WindowManager::getSingletonPtr();
  CEGUI::String Iptmp;
  CEGUI::String PortTmp;
  unsigned int i = 1;
  if (winMgr->isWindowPresent("Connect/ContainerGrp/Ip"))
    {
      Iptmp = winMgr->getWindow("Connect/ContainerGrp/Ip")->getText();
      PortTmp = winMgr->getWindow("Connect/ContainerGrp/Port")->getText();
      this->ip_ = std::string(Iptmp.c_str());
      this->port_ = StringToNumber<const char *, int>(PortTmp.c_str());
      zappy::Convert *c = new zappy::Convert();
      zappy::Network::initInstance(this->ip_ , this->port_, *c);
      zappy::Network &p = zappy::Network::getInstance();
      p.setParameters(this->port_, this->ip_);
      p.connect_();
      if (p.isConnected())
	{
	  Thread<zappy::Network> t(p);
	  t.start();
	  while (p.gettingMap() && i < 5000)
	    usleep(++i);
	  this->GfxMgr_->hide("Connect");
	  this->GfxMgr_->createRealScene();
	}
    }
  return true;
}

//-------------------------------------------------------------------------------------
bool
NetworkManager::isConnected(void)
{
  if (zappy::Network::getInstancePtr() == NULL)
    return false;
  return zappy::Network::getInstance().isConnected();
}

//-------------------------------------------------------------------------------------
void
NetworkManager::unset(Constants::Selected elem)
{
  if (this->mSelected[elem])
    delete this->mSelected[elem];
  this->mSelected[elem] = NULL;
}

//-------------------------------------------------------------------------------------
void
NetworkManager::set(Constants::Selected elem, std::string &req)
{
  this->mSelected[elem] = new std::string(req);
}

//-------------------------------------------------------------------------------------
void
NetworkManager::update(void)
{
  std::map<Constants::Selected, std::string *>::iterator it;
  zappy::Network &net = zappy::Network::getInstance();

  for (it = this->mSelected.begin(); it != this->mSelected.end(); ++it)
    if ((*it).second != NULL)
      net.setToSend(*(*it).second);
}

//-------------------------------------------------------------------------------------
void
NetworkManager::updateBox(unsigned int x, unsigned int y)
{
  std::string s;

  s = "bct " + NumberToString<unsigned int>(x) +
    " " + NumberToString<unsigned int>(y) + "\n";
  this->set(Constants::GROUND, s);
}

//-------------------------------------------------------------------------------------
void
NetworkManager::updateBag(unsigned int id)
{
  std::string s;

  s = "pin " + NumberToString<unsigned int>(id) + "\n";;
  this->set(Constants::PLAYER, s);
}

//-------------------------------------------------------------------------------------
bool
NetworkManager::updateTime(const CEGUI::EventArgs&)
{
  CEGUI::WindowManager *winMgr = CEGUI::WindowManager::getSingletonPtr();
  std::string time;
  std::string s;

  if (winMgr->isWindowPresent("Time/Container/Time"))
    {
      zappy::Network &net = zappy::Network::getInstance();

      time = winMgr->getWindow("Time/Container/Time")->getText().c_str();
      s = "sst " + time + "\n";
      net.setToSend(s);
    }
  return true;
}
