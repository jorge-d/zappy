/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Thu Jul  7 16:51:48 2011 dimitri jorge
*/

#include <stdio.h>
#include "options.h"
#include "zappy.h"

int		connect_nbr(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  int		nb;
  char		buff[128];

  printf(CYAN"There are %d players in team '%s'"END, player_list_size(p->t),
	 p->t->name);
  nb = (c->options->auth_clients - player_list_size(p->t) + p->t->nb_fork);
  snprintf(buff, sizeof(buff), "%d", nb);
  jm_writeln(cli, buff);
  return (0);
}
