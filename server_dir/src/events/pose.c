/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Sat Jul  9 15:05:50 2011 jose rodrigues
*/

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
  if (*(int *)((char *)p + gl_cmp[i].off))
    {
      *(int *)((char *)p + gl_cmp[i].off) -= 1;
      push_elem_on_map(c, NULL, p->x, p->y, gl_cmp[i].elem);
      gfx_player_throws_object(c, p, gl_cmp[i].elem);
      jm_writeln(cli, "ok");
    }
  else
    jm_writeln(cli, "ko");
  return (0);
}

int		pose(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  char		*s;
  unsigned	i;

  i = 0;
  s = p->e->param;
  if (s[0])
    s += 1;
  printf(GREEN"Player %d wants to drop '%s'"END, p->id, s);
  while (i < sizeof(gl_cmp) / sizeof(*gl_cmp))
    {
      if (!strcmp(gl_cmp[i].name, s) && *(int *)((char *)p + gl_cmp[i].off))
	{
	  edit_map_(c, cli, p, i);
	  return (0);
	}
      ++i;
    }
  jm_writeln(cli, "ko");
  return (0);
}
