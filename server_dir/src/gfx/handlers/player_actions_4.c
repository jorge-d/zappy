/*
** player_actions_4.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx/handlers
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Thu Jun 23 19:19:14 2011 dimitri jorge
** Last update Thu Jun 23 19:26:15 2011 dimitri jorge
*/

#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"
#include "gfx.h"

void		gfx_player_moves(t_ctrl *c, t_player *p)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	ppo(c, l, p->id);
      l = l->next;
    }
}

