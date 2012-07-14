/*
** opt_teams.c for zappy in /home/rodrig_d/rendu/c/zappy/server
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Tue Jun 14 15:04:55 2011 jose rodrigues
** Last update Sun Jul 10 21:02:32 2011 jose rodrigues
*/

#include <stdlib.h>
#include <stdio.h>
#include "options.h"

static t_team	*add_node_(t_team *node, char *teamname)
{
  t_team	*new;

  if ((new = malloc(sizeof(*new))) == NULL)
    {
      perror("malloc");
      return (NULL);
    }
  new->name = teamname;
  new->nblvlmax = 0;
  new->nb_fork = 0;
  new->players = NULL;
  new->next = node;
  new->prev = NULL;
  if (node)
    node->prev = new;
  return (new);
}

int		opt_teams(int ac, char **av, int i, t_opts *op)
{
  int		j;

  ++i;
  j = 0;
  if (i >= ac || av[i][0] == '-')
    return (-1);
  while (i < ac && av[i][0] != '-')
    {
      if ((op->teams = add_node_(op->teams, av[i])) == NULL)
	return (-1);
      ++i;
      ++j;
    }
  if (j < 2)
    return (-1);
  return (0);
}
