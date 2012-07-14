/*
** functions_2.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 17:34:01 2011 dimitri jorge
** Last update Mon Jun 27 13:32:49 2011 jose rodrigues
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void		ppo(t_ctrl *c, t_jm_list *l, int id)
{
  char		buff[64];
  t_player	*p;

  if ((p = get_player_from_id(c, id)))
    {
      snprintf(buff, sizeof(buff) - 1, "ppo %d %d %d %d",
	       id, p->x, p->y, p->d + 1);
      jm_writeln(l, buff);
    }
  else
    sbp(l);
}

void		plv(t_ctrl *c, t_jm_list *l, int id)
{
  char		buff[64];
  t_player	*p;

  if ((p = get_player_from_id(c, id)))
    {
      snprintf(buff, sizeof(buff) - 1, "plv %d %d", id, p->lvl);
      jm_writeln(l, buff);
    }
  else
    sbp(l);
}

void		pin(t_ctrl *c, t_jm_list *l, int id)
{
  char		buff[128];
  t_player	*p;
  t_inventory	*i;

  if ((p = get_player_from_id(c, id)))
    {
      i = &p->inventory;
      snprintf(buff, sizeof(buff) - 1,
	       "pin %d %d %d %d %d %d %d %d %d %d", id, p->x, p->y,
	       p->food, i->linemate, i->deraumere, i->sibur, i->mendiane,
	       i->phiras, i->thystame);
      jm_writeln(l, buff);
    }
  else
    sbp(l);
}

void	pex(t_jm_list *l, int id)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "pex %d", id);
  jm_writeln(l, buff);
}

void	pbc(t_jm_list *l, int id, char *s)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "pbc %d ", id);
  jm_write(l, buff);
  jm_writeln(l, s);
}
