/*
** functions_1.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 17:28:46 2011 dimitri jorge
** Last update Tue Jul  5 17:29:59 2011 dimitri jorge
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void	msz(t_ctrl *c, t_jm_list *l)
{
  char	buff[64];

  snprintf(buff, sizeof(buff) - 1, "msz %d %d",
	   c->options->map_x, c->options->map_y);
  jm_writeln(l, buff);
}

void	bct(t_ctrl *c, t_jm_list *l, int x, int y)
{
  char	buff[128];

  snprintf(buff, sizeof(buff) - 1, "bct %d %d %d %d %d %d %d %d %d", x, y,
	   get_nb_object(c, x, y, NOURRITURE), get_nb_object(c, x, y, LINEMATE),
	   get_nb_object(c, x, y, DERAUMERE), get_nb_object(c, x, y, SIBUR),
	   get_nb_object(c, x, y, MENDIANE), get_nb_object(c, x, y, PHIRAS),
	   get_nb_object(c, x, y, THYSTAME));
  jm_writeln(l, buff);
}

void	mct(t_ctrl *c, t_jm_list *l)
{
  int	x;
  int	y;

  y = 0;
  while (y < getmapy(c))
    {
      x = 0;
      while (x < getmapx(c))
	{
	  bct(c, l, x, y);
	  x++;
	}
      y++;
    }
}

void		tna(t_ctrl *c, t_jm_list *l)
{
  t_team	*t;

  t = c->teams;
  while (t)
    {
      jm_write(l, "tna ");
      jm_writeln(l, t->name);
      t = t->next;
    }
}

void	pnw(t_jm_list *l, t_player *p)
{
  char	buff[128];

  snprintf(buff, sizeof(buff) - 1, "pnw %d %d %d %d %d ",
	   p->id, p->x, p->y, p->d + 1, p->lvl);
  jm_write(l, buff);
  jm_writeln(l, p->t->name);
}
