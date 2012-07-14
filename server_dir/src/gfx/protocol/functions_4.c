/*
** functions_4.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 17:42:14 2011 dimitri jorge
** Last update Thu Jun 23 19:12:29 2011 dimitri jorge
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void	pdi(t_jm_list *l, t_player *p)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "pdi %d", p->id);
  jm_writeln(l, buff);
}

void	enw(t_jm_list *l, int idp, t_eclode *o)
{
  char	buff[64];

  snprintf(buff, sizeof(buff) - 1, "enw %d %d %d %d", o->id, idp, o->x, o->y);
  jm_writeln(l, buff);
}

void	eht(t_jm_list *l, t_eclode *o)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "eht %d", o->id);
  jm_writeln(l, buff);
}

void	ebo(t_jm_list *l, t_player *p)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "ebo %d", p->id);
  jm_writeln(l, buff);
}

void	edi(t_jm_list *l, t_player *p)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "edi %d", p->id);
  jm_writeln(l, buff);
}
