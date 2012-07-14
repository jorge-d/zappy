/*
** player_actions_3.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx/handlers
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 19:34:26 2011 dimitri jorge
** Last update Mon Jun 27 13:35:34 2011 jose rodrigues
*/

#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"
#include "gfx.h"

void		gfx_player_fork_end(t_ctrl *c, t_player *p, t_eclode *o)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	enw(l, p->id, o);
      l = l->next;
    }
}

void		gfx_egg_hatched(t_ctrl *c, t_eclode *o)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	eht(l, o);
      l = l->next;
    }
}

void		gfx_player_connect_egg(t_ctrl *c, t_player *p)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	ebo(l, p);
      l = l->next;
    }
}

void		gfx_egg_died(t_ctrl *c, t_player *p)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	edi(l, p);
      l = l->next;
    }
}

void		gfx_end_of_game(t_ctrl *c, char *teamname)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	seg(l, teamname);
      l = l->next;
    }
}
