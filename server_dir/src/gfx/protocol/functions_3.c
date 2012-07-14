/*
** functions_3.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 17:38:31 2011 dimitri jorge
** Last update Mon Jun 27 13:33:08 2011 jose rodrigues
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void	plc(t_jm_list *l, t_player *p, int *ids)
{
  char	buff[64];
  int	i;

  i = 0;
  snprintf(buff, sizeof(buff) - 1, "pic %d %d %d %d",
	   p->x, p->y, p->lvl, p->id);
  if (ids[i] != 0)
    {
      jm_write(l, buff);
      while (ids[i + 1] != 0)
	{
	  snprintf(buff, sizeof(buff) - 1, " %d", ids[i]);
	  jm_write(l, buff);
	  i++;
	}
      snprintf(buff, sizeof(buff) - 1, " %d", ids[i]);
    }
  jm_writeln(l, buff);
}

void	ple(t_jm_list *l, t_player *p, char res)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "pie %d %d %c", p->x, p->y, res);
  jm_writeln(l, buff);
}

void	pfk(t_jm_list *l, t_player *p)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "pfk %d", p->id);
  jm_writeln(l, buff);
}

void	pdr(t_jm_list *l, t_player *p, e_elem t)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "pdr %d %d", p->id, t);
  jm_writeln(l, buff);
}

void	pgt(t_jm_list *l, t_player *p, e_elem t)
{
  char	buff[32];

  snprintf(buff, sizeof(buff) - 1, "pgt %d %d", p->id, t);
  jm_writeln(l, buff);
}
