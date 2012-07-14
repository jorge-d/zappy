##
## Makefile
## Login : <sabbag_a@new-host-4>
## Started on  Sat Jun 11 16:31:23 2011 fares sabbagh
## $Id$
##
## Author(s):
##  - fares sabbagh <fares.sabbagh@epitech.eu>
##
## Copyright (C) 2011 fares sabbagh
## This program is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 3 of the License, or
## (at your option) any later version.
##
## This program is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.
##
## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
##

##############################
# Main of Makefile	     #
##############################
NAME 	=	zappy


SRC_DIR	=	src/
SRC_OGRE =	$(SRC_DIR)Ogre/
SRC_NET =	$(SRC_DIR)Network/

INC_DIR =	inc/
INC_OGRE =	$(INC_DIR)Ogre/
INC_NET =	$(INC_DIR)Network/

SRC	=	$(SRC_OGRE)main.cpp		\
		$(SRC_OGRE)NetworkManager.cpp	\
		$(SRC_OGRE)GraphicsManager.cpp	\
		$(SRC_OGRE)OgreMain.cpp		\
		$(SRC_OGRE)CEGUIManager.cpp	\
		$(SRC_OGRE)PlayersManager.cpp	\
		$(SRC_OGRE)BoxesManager.cpp	\
		$(SRC_OGRE)ORessource.cpp	\
		$(SRC_OGRE)OPlayer.cpp		\
		$(SRC_OGRE)RessourceFactory.cpp	\
		$(SRC_OGRE)Mutex.cpp		\
		$(SRC_OGRE)scopedLock.cpp	\
		$(SRC_NET)Box.cpp		\
		$(SRC_NET)Egg.cpp		\
		$(SRC_NET)Grid.cpp		\
		$(SRC_NET)Network.cpp		\
		$(SRC_NET)Convert.cpp		\
		$(SRC_NET)excp.cpp		\
		$(SRC_NET)Player.cpp		\
		$(SRC_NET)Team.cpp


PCH_SRC = 	$(INC_OGRE)OgreMain.h.gch	\
		$(INC_OGRE)CEGUIMain.h.gch

INCL  	=	$(INC_OGRE)GraphicsManager.h	\
		$(INC_OGRE)CEGUIManager.h	\
		$(INC_OGRE)NetworkManager.h	\
		$(INC_OGRE)PlayersManager.h	\
		$(INC_OGRE)BoxesManager.h	\
		$(INC_OGRE)RessourceFactory.h	\
		$(INC_OGRE)Tools.h		\
		$(INC_NET)Box.hh		\
		$(INC_NET)Egg.hh		\
		$(INC_NET)Grid.hh		\
		$(INC_NET)Network.hh		\
		$(INC_NET)Convert.hh		\
		$(INC_NET)Player.hh		\
		$(INC_OGRE)Mutex.hh		\
		$(INC_OGRE)scopedLock.hh

################
# Optional add #
################

IPATH	=  -I/usr/local/include/OIS/
IPATH	+= -I/usr/local/include/OGRE/
IPATH	+= -I/usr/local/include/CEGUI/
IPATH	+= -I/usr/include/OIS/
IPATH	+= -I/usr/include/OGRE/

IPATH	+= -I$(INC_OGRE)
IPATH	+= -I$(INC_NET)

# LPATH    = -L/usr/local/lib/
# LPATH    += -L/usr/lib/

#####################
# Macro Definitions #
#####################
CXX 	?= g++
MAKE 	?= make
CP      ?= cp
SHELL	?= /bin/bash
RM 	?= /bin/rm -f
COMP	?= gzip -9v
UNCOMP	?= gzip -df
STRIP	?= strip
PRINTF	?= printf
FORCE_COMPILE := .mFlags

OBJS     = $(SRC:.cpp=.o)

OPTFLAGS	=  $(if $(OPT), -O$(OPT), -O0)
CXXFLAGS	+= -Wall -ansi -pipe
CXXFLAGS	+= $(OPTFLAGS)

LDFLAGS +=  -lOgreMain -lOgreTerrain -lpthread -lOIS -lCEGUIBase -lCEGUIOgreRenderer
MYCXXFLAGS  = $(CXXFLAGS) $(IPATH)

.SUFFIXES: .h.Z .c.Z .h.gz .c.gz .c.z .h.z .h.gch

##############################
# Basic Compile Instructions #
##############################

all:	$(NAME)
	@ $(PRINTF) "\033[31m[Executable Name]\033[m ---> $(NAME)\n"
	@ $(PRINTF) "\033[31m[CLAGS]\033[m ---> $(CXXFLAGS)\n"


$(NAME): $(FORCE_COMPILE) $(PCH_SRC) $(OBJS) $(SRC) $(INCL)
	@ $(CXX) $(OBJS) $(LDFLAGS) -o $(NAME)

clean:
	@ $(RM) $(OBJS) $(PCH_SRC) *.log
	@ $(PRINTF) "\033[31m[Clean Ok]\033[m\n"

fclean: clean
	@ $(RM) $(NAME)
	@ $(PRINTF) "\033[31m[Fclean Ok]\033[m\n"

re:	fclean all

strip: all
	$(STRIP) ./$(NAME)

comp: clean
	$(COMP) $(INCL) $(SRC)

ucomp:
	$(UNCOMP) $(SRC) $(INCL)

############################################################
# Tricks to force compilation if CXXFLAGS changed	   #
############################################################

$(FORCE_COMPILE): force
		@ echo '$(MYCXXFLAGS)' | cmp -s $@ || (echo '$(MYCXXFLAGS)' > $@; make fclean) #if someone can make flcean..

##############################
# .y.z Rules		     #
##############################

.c.Z.c .h.Z.h .c.gz.c .h.gz.h .c.z.c .h.z.h :
	$(UNCOMP) $<

.cpp.o:
	@ $(PRINTF) "\033[31m[OK]\033[m ---> $<\n"
	@ $(CXX) -o $@ $(MYCXXFLAGS) -c $<

 .h.h.gch:
	@ $(PRINTF) "\033[31m[PreCompiled Header]\033[m ---> $<\n"
	@ $(CXX) -o $@ $(MYCXXFLAGS) -c $<

.PHONY: force
