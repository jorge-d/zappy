/*
** Tools.h
** Login : <sabmit@Sabmit-Ubuntu>
** Started on  Mon Jun 20 19:03:52 2011 Sabmit
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

#ifndef   	TOOLS_H_
# define   	TOOLS_H_

#include <iostream>

template<typename T>
std::string NumberToString(T Number)
{
  std::stringstream ss;

  ss << Number;
  return ss.str();
}

template<typename T, typename B>
B StringToNumber(T str)
{
   std::stringstream ss(str);
  B Number;

  ss >> Number;
  return Number;
}

#endif 	    /* !TOOLS_H_ */
