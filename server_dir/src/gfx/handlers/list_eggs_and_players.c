/*
** list_eggs_and_players.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 20:19:32 2011 dimitri jorge
** Last update Wed Jun 22 20:35:17 2011 dimitri jorge
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "options.h"
#include "zappy.h"
#include "gfx.h"

void		list_eggs_and_players(t_ctrl *c, t_jm_list *l)
{
  t_eclode	*o;
  t_team	*t;
  t_player	*p;

  t = c->teams;
  while (t)
    {
      p = t->players;
      while (p)
	{
	  pnw(l, p);
	  p = p->next;
	}
      t = t->next;
    }
  o = c->eggs;
  while (o)
    {
      enw(l, o->id_parent, o);
      o = o->next;
    }
}
