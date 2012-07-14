/*
** player_join.c for zappy in /home/jorge_d/svn/zappy/server_dir/src
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 18:12:53 2011 dimitri jorge
** Last update Thu Jun 23 19:40:56 2011 dimitri jorge
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "options.h"
#include "zappy.h"
#include "gfx.h"

void		gfx_player_join(t_ctrl *c, t_player *p)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	pnw(l, p);
      l = l->next;
    }
}

void		gfx_player_expulse(t_ctrl *c, t_player *p, int *ids)
{
  t_jm_list	*l;
  int		i;

  i = 0;
  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	{
	  pex(l, p->id);
	  while (ids[i])
	    {
	      ppo(c, l, ids[i]);
	      i++;
	    }
	}
      l = l->next;
    }
}

void		gfx_player_broadcast(t_ctrl *c, t_player *p, char *s)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	pbc(l, p->id, s);
      l = l->next;
    }
}

static void	_fill_ids(t_ctrl *c, t_player *p, int *ids)
{
  t_frame	*f;
  t_player	*tmp;
  int		i;

  i = 0;
  f = getframe(c, p->x, p->y);
  while (f)
    {
      if (f->type == PLAYER && (tmp = f->p) && tmp != p && tmp->lvl == p->lvl)
	ids[i++] = tmp->id;
      f = f->next;
    }
  ids[i] = 0;
}

void		gfx_player_begin_incantation(t_ctrl *c, t_player *p)
{
  t_jm_list	*l;
   int		*ids;

  if ((ids = calloc(get_nb_players(c, p->x, p->y, p->lvl) + 1, sizeof(*ids))))
    {
      _fill_ids(c, p, ids);
      l = c->l;
      while (l)
	{
	  if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	    plc(l, p, ids);
	  l = l->next;
	}
      free(ids);
    }
}
