/*
** dispatch_elems.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Thu Jun 23 17:19:59 2011 jose rodrigues
** Last update Thu Jul  7 15:17:42 2011 jose rodrigues
*/

#include <stdlib.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void		dispatch_elems(t_ctrl *c, int x, int y)
{
  t_frame	*tmp;
  t_frame	*tmp2;
  int		newx;
  int		newy;

  tmp = getframe(c, x, y);
  while (tmp)
    {
      tmp2 = tmp->next;
      if (tmp->type != PLAYER)
	{
	  unset_elem_from_map(c, tmp, x, y);
	  newx = rand() % c->options->map_x;
	  newy =  rand() % c->options->map_y;
	  set_elem_on_map(c, tmp, newx, newy);
	  gfx_send_frame_content(c, newx, newy);
	}
      tmp = tmp2;
    }
  gfx_send_frame_content(c, x, y);
}
