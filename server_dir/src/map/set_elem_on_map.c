/*
** set_elem_on_map.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir/src/map
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 17:08:10 2011 jose rodrigues
** Last update Wed Jul  6 18:09:50 2011 jose rodrigues
*/

#include <stdio.h>
#include <stdlib.h>
#include "zappy.h"
#include "options.h"

void		set_elem_on_map(t_ctrl *c, t_frame *node, int x, int y)
{
  t_frame	*old;

  node->next = NULL;
  node->prev = NULL;
  if ((old = getframe(c, x, y)))
    {
      old->prev = node;
      node->next = old;
    }
  getframe(c, x, y) = node;
}
