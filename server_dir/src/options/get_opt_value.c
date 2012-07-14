/*
** get_opt_value.c for zappy in /home/rodrig_d/rendu/c/zappy/server
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Mon Jun 13 17:21:04 2011 jose rodrigues
** Last update Tue Jun 14 16:31:37 2011 jose rodrigues
*/

#include <stdlib.h>

char		*get_opt_value(int ac, char **av, int i)
{
  if (av[i][2] != '\0')
    return (av[i] + 2);
  else if (i + 1 < ac)
    return (av[i + 1]);
  return (NULL);
}
