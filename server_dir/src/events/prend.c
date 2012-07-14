/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Sat Jul  9 15:09:48 2011 jose rodrigues
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "zappy.h"
#include "gfx.h"

static t_pp	gl_cmp[] =
  {
    {"nourriture", NOURRITURE, ((off_t)&((t_player *)0)->food) },
    {"linemate", LINEMATE, ((off_t)&((t_player *)0)->inventory.linemate)},
    {"deraumere", DERAUMERE, ((off_t)&((t_player *)0)->inventory.deraumere)},
    {"sibur", SIBUR, ((off_t)&((t_player *)0)->inventory.sibur)},
    {"mendiane", MENDIANE, ((off_t)&((t_player *)0)->inventory.mendiane)},
    {"phiras", PHIRAS, ((off_t)&((t_player *)0)->inventory.phiras)},
    {"thystame", THYSTAME, ((off_t)&((t_player *)0)->inventory.thystame)}
  };

static int	edit_map_(t_ctrl *c, t_jm_list *cli, t_player *p, int i)
{
  t_frame	*tmp;

  if ((tmp = get_elem_from_map(c, p->x, p->y, gl_cmp[i].elem)))
    {
      *(int *)((char *)p + gl_cmp[i].off) += 1;
      unset_elem_from_map(c, tmp, p->x, p->y);
      free(tmp);
      jm_writeln(cli, "ok");
      gfx_player_takes_object(c, p, gl_cmp[i].elem);
      return (0);
    }
  else
    jm_writeln(cli, "ko");
  return (0);
}

int		prend(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  char		*s;
  unsigned int	i;

  i = 0;
  if ((s = p->e->param) && s[0])
    s += 1;
  printf(GREEN"Player %d wants to take '%s'"END, p->id, s);
  if (s)
    while (i < sizeof(gl_cmp) / sizeof(*gl_cmp))
      {
	if (!strcmp(gl_cmp[i].name, s))
	  {
	    edit_map_(c, cli, p, i);
	    return (0);
	  }
	++i;
      }
  jm_writeln(cli, "ko");
  return (0);
}
