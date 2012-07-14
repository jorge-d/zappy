/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Sun Jul 10 17:37:42 2011 jose rodrigues
*/

#include <stdlib.h>
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

static void	_expulse_player(t_ctrl *c, t_frame *fra, t_player *p, e_dir d)
{
  int		from;
  int		old_y;
  int		old_x;
  char		buff[64];

  unset_elem_from_map(c, fra, p->x, p->y);
  old_x = p->x;
  old_y = p->y;
  p->x = get_real_map_coord(p->x + gl_ops[d].op_x, getmapx(c));
  p->y = get_real_map_coord(p->y + gl_ops[d].op_y, getmapy(c));
  printf(GREEN"Expulsing player %d to (%d, %d)"END, p->id, p->x, p->y);
  set_elem_on_map(c, fra, p->x, p->y);
  from = get_frame_number(c, p, old_x, old_y);
  snprintf(buff, sizeof(buff) - 1, "deplacement : %d", from);
  jm_writeln(p->fd, buff);
}

static int	_parse_players(t_ctrl *c, t_player *p, int *ids)
{
  t_frame	*f;
  t_frame	*f2;
  int		flag;

  flag = 0;
  f = getframe(c, p->x, p->y);
  while (f)
    {
      f2 = f->next;
      if (f->type == PLAYER && f->p && f->p != p)
	{
	  _expulse_player(c, f, (t_player *)f->p, p->d);
	  ids[flag++] = ((t_player *)f->p)->id;
	}
      f = f2;
    }
  return (flag);
}

int		expulse(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  int		nb;
  int		flag;
  int		*ids;

  flag = 0;
  printf(GREEN"Player %d (%d, %d) makes expulse"END, p->id, p->x, p->y);
  nb = get_nb_object(c, p->x, p->y, PLAYER);
  if (nb > 1 && (ids = calloc(nb, sizeof(*ids))))
    {
      flag = _parse_players(c, p, ids);
      gfx_player_expulse(c, p, ids);
      free(ids);
    }
  if (flag > 0)
    jm_writeln(cli, "ok");
  else
    jm_writeln(cli, "ko");
  return (0);
}
