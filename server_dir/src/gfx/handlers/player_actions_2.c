/*
** player_actions_2.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx/handlers
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 19:02:28 2011 dimitri jorge
** Last update Tue Jul  5 13:11:40 2011 dimitri jorge
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void		gfx_player_end_incantation(t_ctrl *c, t_player *p, int res)
{
  t_jm_list	*l;
  t_frame	*f;
  t_frame	*tmp;

  f = getframe(c, p->x, p->y);
  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	{
	  ple(l, p, (res != 0 ? '1' : '0'));
	  tmp = f;
	  while (tmp)
	    {
	      if (tmp->type == PLAYER && tmp->p)
		plv(c, l, ((t_player *)tmp->p)->id);
	      tmp = tmp->next;
	    }
	}
      l = l->next;
    }
}

void		gfx_player_has_fork(t_ctrl *c, t_player *p)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	pfk(l, p);
      l = l->next;
    }
}

void		gfx_player_throws_object(t_ctrl *c, t_player *p, enum e_elem e)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	{
	  pdr(l, p, e);
	  pin(c, l, p->id);
	  bct(c, l, p->x, p->y);
	}
      l = l->next;
    }
}

void		gfx_player_takes_object(t_ctrl *c, t_player *p, enum e_elem e)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	{
	  pgt(l, p, e);
	  pin(c, l, p->id);
	  bct(c, l, p->x, p->y);
	}
      l = l->next;
    }
}

void		gfx_player_is_dead(t_ctrl *c, t_player *p)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	pdi(l, p);
      l = l->next;
    }
}
