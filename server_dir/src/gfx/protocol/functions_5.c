/*
** functions_5.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 17:43:48 2011 dimitri jorge
** Last update Wed Jun 22 17:54:07 2011 dimitri jorge
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void	sgt(t_ctrl *c, t_jm_list *l)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "sgt %d", c->options->time);
  jm_writeln(l, buff);
}

void	sst(t_ctrl *c, t_jm_list *l, int t)
{
  c->options->time = t;
  sgt(c, l);
}

void	seg(t_jm_list *l, char *n)
{
  jm_write(l, "seg ");
  jm_writeln(l, n);
}

void	smg(t_jm_list *l, char *n)
{
  jm_write(l, "smg ");
  jm_writeln(l, n);
}
