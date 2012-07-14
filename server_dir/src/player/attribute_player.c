/*
** attribute_player.c for zappy in /home/jorge_d/svn/zappy/server_dir/src
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 16:26:27 2011 dimitri jorge
** Last update Sun Jul 10 20:03:49 2011 dimitri jorge
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "options.h"
#include "zappy.h"
#include "gfx.h"

static int	_existing_player(t_ctrl *c, t_jm_list *l, t_player *p)
{
  l->data = p->fd->data;
  if (p->fd->s)
    printf(CYAN"Players #%d is not longer a ghost"END, p->id);
  else
    {
      gfx_player_connect_egg(c, p);
      printf(YELLOW"Players #%d has connected on egg"END, p->id);
    }
  jm_remove_from_list(&c->l, p->fd);
  p->fd = l;
  gfx_player_join(c, p);
  return (1);
}

static int	_is_in_closable(t_closable *clo, t_jm_list *p)
{
  while (clo)
    {
      if (clo->p == p)
	return (1);
      clo = clo->next;
    }
  return (0);
}

int		attribute_player(t_ctrl *c, t_jm_list *l, t_team *t)
{
  t_player	*p;

  p = t->players;
  while (p)
    {
      if (p->fd->fd == -1 && !_is_in_closable(c->to_close, p->fd))
	return (_existing_player(c, l, p));
      p = p->next;
    }
  printf(CYAN"Creating new player #%d"END, c->id_player);
  if (!(p = create_player(c, t, l, c->id_player++)))
    {
      printf(RED"Error creating Player #%d"END, c->id_player - 1);
      return (0);
    }
  ((t_handler*)l->data)->t = IA;
  ((t_handler*)l->data)->p = p;
  printf(CYAN"Player #%d (team %s) at (%d, %d) created"END,
	 p->id, p->t->name, p->x, p->y);
  gfx_player_join(c, p);
  return (1);
}
