/*
** remove_player.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Thu Jun 16 18:27:19 2011 dimitri jorge
** Last update Thu Jul  7 16:13:50 2011 dimitri jorge
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "zappy.h"
#include "event.h"
#include "options.h"

static void	_remove_from_team(t_team *t, t_player *p)
{
  t_player	*prev;
  t_player	*next;

  prev = p->prev;
  next = p->next;
  if (t->nb_fork > 0)
    t->nb_fork--;
  if (!prev)
    {
      if (next)
	next->prev = NULL;
      t->players = next;
    }
  else if (!next)
    prev->next = NULL;
  else
    {
      prev->next = next;
      next->prev = prev;
    }
}

void		remove_player(t_ctrl *c, t_player *p)
{
  t_frame	*tmp;

  if (!p)
    {
      fprintf(stderr, RED"Player doesn't exists"END);
      return ;
    }
  printf(GREEN"Removing player #%d in (%d, %d)"END, p->id, p->x, p->y);
  if (p->lvl >= 8)
    p->t->nblvlmax--;
  remove_life_node(c, p);
  _remove_from_team(p->t, p);
  free_events(p->e);
  p->e = NULL;
  tmp = getframe(c, p->x, p->y);
  while (tmp && (void *)tmp->p != (void *)p)
    tmp = tmp->next;
  if (tmp)
    {
      unset_elem_from_map(c, tmp, p->x, p->y);
      free(tmp);
      free(p);
    }
  else
    fprintf(stderr, RED"Player #%d not found"END, p->id);
}
