/*
** opt_port.c for zappy in /home/rodrig_d/rendu/c/zappy/server
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Mon Jun 13 17:18:07 2011 jose rodrigues
** Last update Tue Jun 14 16:32:35 2011 jose rodrigues
*/

#include <stdlib.h>
#include "options.h"

int		opt_auth_clients(int ac, char **av, int i, t_opts *op)
{
  char		*str;

  if ((str = get_opt_value(ac, av, i)) == NULL)
    return (-1);
  op->auth_clients = atoi(str);
  return (0);
}
