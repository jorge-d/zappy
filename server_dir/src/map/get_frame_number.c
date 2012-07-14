/*
** get_case_number.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/events
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Sun Jun 19 15:23:11 2011 dimitri jorge
** Last update Tue Jul  5 16:11:33 2011 dimitri jorge
*/

#include "zappy.h"
#include "options.h"

static t_turn	gl_ops[] =
  {
    {1, 0, -1},
    {2, -1, -1},
    {3, -1, 0},
    {4, -1, 1},
    {5, 0, 1},
    {6, 1, 1},
    {7, 1, 0},
    {8, 1, -1}
  };

static int	_get_nb(int val, int s)
{
  int		nb;

  if ((nb = val - s) > 0)
    return (nb);
  return (8 + nb);
}

int		get_frame_number(t_ctrl *c, t_player *p, int x, int y)
{
  int		s;
  unsigned int	i;
  int		real_x;
  int		real_y;

  i = 0;
  if (p->x == x && p->y == y)
    return 0;
  if (p->d == UP)
    s = 0;
  else if (p->d == RIGHT)
    s = 6;
  else if (p->d == DOWN)
    s = 4;
  else
    s = 2;
  while (i < (sizeof(gl_ops) / sizeof(*gl_ops)))
    {
      real_x = get_real_map_coord(p->x + gl_ops[i].x, getmapx(c));
      real_y = get_real_map_coord(p->y + gl_ops[i].y, getmapy(c));
      if (real_x == x && real_y == y)
	  return _get_nb(gl_ops[i].val, s);
      i++;
    }
  return -1;
}
