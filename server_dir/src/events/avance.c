/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Thu Jul  7 16:43:18 2011 dimitri jorge
*/

#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

static t_op_coord	gl_ops[] =
  {
    {0, -1},
    {-1, 0},
    {0, 1},
    {1, 0}
  };

int		avance(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  t_frame	*fra;

  fra = get_elem_from_map(c, p->x, p->y, ALL);
  while (fra)
    {
      if (fra->type == PLAYER && fra->p == p)
	{
	  unset_elem_from_map(c, fra, p->x, p->y);
	  p->x = get_real_map_coord(p->x + gl_ops[p->d].op_x, getmapx(c));
	  p->y = get_real_map_coord(p->y + gl_ops[p->d].op_y, getmapy(c));
	  set_elem_on_map(c, fra, p->x, p->y);
	  printf(GREEN"Player %d is moving to (%d, %d)"END, p->id, p->x, p->y);
	  gfx_player_moves(c, p);
	  jm_writeln(cli, "ok");
	  return (0);
	}
      fra = fra->next;
    }
  fprintf(stderr, "Error in 'avance' function\n");
  return (0);
}
