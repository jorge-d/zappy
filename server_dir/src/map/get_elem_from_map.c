/*
** get_elem_from_map.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Sat Jun 18 11:38:08 2011 jose rodrigues
** Last update Sun Jun 19 14:42:33 2011 dimitri jorge
*/

#include <stdlib.h>
#include "zappy.h"
#include "options.h"

t_frame		*get_elem_from_map(t_ctrl *c, int x, int y, e_elem e)
{
  t_frame	*b;

  b = getframe(c, x, y);
  if (e == ALL)
    return (b);
  while (b)
    {
      if (b->type == e)
	return (b);
      b = b->next;
    }
  return (NULL);
}
