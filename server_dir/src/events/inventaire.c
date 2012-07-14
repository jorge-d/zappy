/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Thu Jul  7 16:46:13 2011 dimitri jorge
*/

#include <stdio.h>
#include "zappy.h"

int	inventaire(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  char	buff[1024];

  (void)c;
  snprintf(buff, sizeof(buff) - 1, "{nourriture %d, linemate %d, "
	   "deraumere %d, sibur %d, mendiane %d, phiras %d, thystame %d}",
	   p->food, p->inventory.linemate, p->inventory.deraumere,
	   p->inventory.sibur, p->inventory.mendiane, p->inventory.phiras,
	   p->inventory.thystame);
  jm_writeln(cli, buff);
  printf(GREEN"Player %d is requesting his inventory"END, p->id);
  return (0);
}
