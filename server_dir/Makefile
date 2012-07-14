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

SRCDIR	=	src/
HDRDIR	=	inc/
OBJDIR	=	obj/
LIBDIR	=	lib/
NETDIR	=	$(LIBDIR)networklib/
VPATH	=	$(SRCDIR):$(HDRDIR):$(NETDIR)

EXEC	=	server

EVENT_FUNC	=	events/
MAP_FUNC	=	map/
OPTION_FUNC	=	options/
PLAYER_FUNC	=	player/
GFX_FUNC	=	gfx/
FREE_FUNC	=	free_functions/

##########################################
### Add '.c' source files here :
### 	path/to/source.c
##########################################
SRCS	=	$(EVENT_FUNC)avance.c			\
		$(EVENT_FUNC)broadcast.c		\
		$(EVENT_FUNC)connect_nbr.c		\
		$(EVENT_FUNC)droite.c			\
		$(EVENT_FUNC)event_list_functions.c	\
		$(EVENT_FUNC)expulse.c			\
		$(EVENT_FUNC)fork_z.c			\
		$(EVENT_FUNC)gauche.c			\
		$(EVENT_FUNC)handle_events.c		\
		$(EVENT_FUNC)incantation.c		\
		$(EVENT_FUNC)inventaire.c		\
		$(EVENT_FUNC)pose.c			\
		$(EVENT_FUNC)prend.c			\
		$(EVENT_FUNC)voir.c			\
		\
		$(FREE_FUNC)closable_functions.c	\
		$(FREE_FUNC)free_control.c		\
		\
		$(GFX_FUNC)handle_gfx.c			\
		$(GFX_FUNC)handle_protocol.c		\
		$(GFX_FUNC)handle_protocol_2.c		\
		$(GFX_FUNC)protocol/functions_1.c	\
		$(GFX_FUNC)protocol/functions_2.c	\
		$(GFX_FUNC)protocol/functions_3.c	\
		$(GFX_FUNC)protocol/functions_4.c	\
		$(GFX_FUNC)protocol/functions_5.c	\
		$(GFX_FUNC)handlers/player_actions_1.c	\
		$(GFX_FUNC)handlers/player_actions_2.c	\
		$(GFX_FUNC)handlers/player_actions_3.c	\
		$(GFX_FUNC)handlers/player_actions_4.c	\
		$(GFX_FUNC)handlers/server_messages.c	\
		$(GFX_FUNC)handlers/list_eggs_and_players.c	\
		\
		start_zappy.c				\
		handle_commands.c			\
		handle_type.c				\
		init_server.c				\
		get_commands.c				\
		main.c					\
		\
		$(MAP_FUNC)get_nb_object.c		\
		$(MAP_FUNC)get_player_from_id.c		\
		$(MAP_FUNC)get_elem_from_map.c		\
		$(MAP_FUNC)get_frame_number.c		\
		$(MAP_FUNC)push_elem_on_map.c		\
		$(MAP_FUNC)set_elem_on_map.c		\
		$(MAP_FUNC)unset_elem_from_map.c	\
		$(MAP_FUNC)get_real_map_coord.c		\
		$(MAP_FUNC)generate_elems.c		\
		$(MAP_FUNC)get_nb_elems.c		\
		$(MAP_FUNC)dispatch_elems.c		\
		\
		$(PLAYER_FUNC)handle_eclosion.c		\
		$(PLAYER_FUNC)elevate_players.c		\
		$(PLAYER_FUNC)handle_life.c		\
		$(PLAYER_FUNC)create_player.c		\
		$(PLAYER_FUNC)attribute_player.c	\
		$(PLAYER_FUNC)life_functions.c		\
		$(PLAYER_FUNC)player_list_size.c	\
		$(PLAYER_FUNC)remove_player.c		\
		\
		$(OPTION_FUNC)free_options.c		\
		$(OPTION_FUNC)get_opt_value.c		\
		$(OPTION_FUNC)get_opts.c		\
		$(OPTION_FUNC)opt_auth_clients.c	\
		$(OPTION_FUNC)opt_map_x.c		\
		$(OPTION_FUNC)opt_map_y.c		\
		$(OPTION_FUNC)opt_port.c		\
		$(OPTION_FUNC)opt_teams.c		\
		$(OPTION_FUNC)opt_time.c

NETSRCS	=	jm_free_functions.c	\
		jm_init_client.c	\
		jm_init_server.c	\
		jm_handle_read.c	\
		jm_handle_write.c	\
		jm_add_client.c		\
		jm_push_fd.c		\
		jm_select.c

# End of source files

##########################################
### Add '.h' header files here :
### 	path/to/header.h
##########################################
HDRS	=
# End of header files

OBJS	=	$(SRCS:%.c=$(OBJDIR)/%.o)
LOBJS	=	$(NETSRCS:%.c=$(OBJDIR)/%.o)

CC	=	gcc
CFLAGS	+=	-Wall -Wextra
CFLAGS	+=	$(if $(DF),-ggdb,-O3)
CFLAGS	+=	$(INCLUDE)
INCLUDE	=	-I. -I$(HDRDIR)
LDFLAGS	=	-lm

PRINTF	=	/usr/bin/printf
END	=	\033[m
GREEN	=	\033[32m
RED	=	\033[31m


##########################################
### Rules
##########################################

all		: $(EXEC)

$(EXEC)		: $(OBJS) $(LOBJS) $(HDRS)
		@$(CC) $(OBJS) $(LOBJS) $(LDFLAGS) -o $(EXEC)
		@$(PRINTF) "$(GREEN)[OK]$(END) $@ successfully linked\n"

clean		:
		@$(RM) $(OBJS)
		@$(RM) $(LOBJS)
		@$(PRINTF) "$(RED)[OK]$(END) CLEAN $(EXEC) - objs\n"

fclean		: clean
		@$(RM) $(EXEC)
		@$(PRINTF) "$(RED)[OK]$(END) FCLEAN $(EXEC)\n"

re		: fclean all

$(OBJDIR)/%.o	: %.c
		@$(CC) $(CFLAGS) -c $< -o $@
		@$(PRINTF) "$(GREEN)[OK]$(END) --> $< \n"

.PHONY		: all clean fclean re
