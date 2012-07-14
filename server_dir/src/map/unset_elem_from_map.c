/*
** unset_elem_from_map.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir/src/map
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 17:07:14 2011 jose rodrigues
** Last update Mon Jul  4 15:20:46 2011 dimitri jorge
*/

#include <stdio.h>
#include <stdlib.h>
#include "zappy.h"
#include "options.h"

void		reset_player_into_map(t_ctrl *c, t_player *p, int x, int y)
{
  t_frame	*tmp;

  tmp = getframe(c, p->x, p->y);
  while (tmp && (void *)tmp->p != (void *)p)
    tmp = tmp->next;
  if (tmp)
    {
      unset_elem_from_map(c, tmp, p->x, p->y);
      set_elem_on_map(c, tmp, x, y);
      p->x = x;
      p->y = y;
    }
  else
    fprintf(stderr, "A strange error occured in reset_player_into_map\n");
}

void		unset_elem_from_map(t_ctrl *c, t_frame *node, int x, int y)
{
  t_frame	*prev;
  t_frame	*next;

  prev = node->prev;
  next = node->next;
  if (!prev)
    {
      if (next)
	next->prev = NULL;
      getframe(c, x, y) = next;
    }
  else
    {
      if (next)
	next->prev = prev;
      prev->next = next;
    }
}
