/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Thu Jul  7 16:42:42 2011 dimitri jorge
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

static int	get_coord_(int s, int d, int size)
{
  if (s == d)
    return (d);
  else if (s < d)
    return ((abs(d - s) <= size / 2) ? (d - 1) : (d + 1));
  else
    return ((abs(d - s) <= size / 2) ? (d + 1) : (d - 1));
  return (0);
}

static int	send_sound_dir_(t_ctrl *c, t_jm_list *src, t_jm_list *dest)
{
  t_player	*s;
  t_player	*d;
  int		x;
  int		y;
  char		p[2];

  bzero(p, sizeof(p));
  s = ((t_handler *)src->data)->p;
  d = ((t_handler *)dest->data)->p;
  x = get_coord_(s->x, d->x, getmapx(c));
  y = get_coord_(s->y, d->y, getmapy(c));
  p[0] = get_frame_number(c, d, get_real_map_coord(x, getmapx(c)),
			  get_real_map_coord(y, getmapy(c))) + '0';
  jm_write(dest, p);
  jm_write(dest, ",");
  return (0);
}

int		broadcast(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  char		*s;
  t_jm_list	*tmp;

  (void)cli;
  s = p->e->param;
  if (s[0])
    s += 1;
  printf(GREEN"Player %d (%d, %d) is broadcasting"END, p->id, p->x, p->y);
  tmp = c->l;
  while (tmp)
    {
      if (tmp != cli && tmp->data && ((t_handler *)tmp->data)->t == IA)
	{
	  jm_write(tmp, "message ");
	  send_sound_dir_(c, cli, tmp);
	  jm_writeln(tmp, s);
	}
      tmp = tmp->next;
    }
  gfx_player_broadcast(c, p, s);
  jm_writeln(cli, "ok");
  return (0);
}
