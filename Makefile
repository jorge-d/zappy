##
## Makefile for zappy in /home/arno/workspace/zappy
## 
## Made by arnaud mesureur
## Login   <arnaud.mesureur@epitech.net>
## 
## Started on  Wed Dec 23 02:55:28 2009 arnaud mesureur
##

##########################################
### Variables
##########################################

SHELL	=	/bin/sh

SERVER	=	server

SERVER_DIR	=	server_dir

ECHO	=	echo

CP	=	/bin/cp
RM	=	rm -f

##########################################
### Rules
##########################################

all		: $(SERVER)

$(SERVER)	:
		@$(MAKE) -C $(SERVER_DIR)
		@$(CP) $(SERVER_DIR)/$(SERVER) .
		@$(ECHO) "[OK] Building server"

clean		:
		@$(MAKE) -C $(SERVER_DIR) clean

fclean		:
		@$(MAKE) -C $(SERVER_DIR) fclean
		@$(RM) $(SERVER)

re		: fclean all

.PHONY		: all clean fclean re
