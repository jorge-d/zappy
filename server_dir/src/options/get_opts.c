/*
** get_opts.c for zappy in /home/rodrig_d/rendu/c/zappy/server
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Mon Jun 13 16:40:25 2011 jose rodrigues
** Last update Sun Jul 10 21:02:46 2011 jose rodrigues
*/

#include <stdlib.h>
#include <stdio.h>
#include "options.h"

static t_funcs gl_f[] =
  {
    {'p', opt_port},
    {'x', opt_map_x},
    {'y', opt_map_y},
    {'n', opt_teams},
    {'c', opt_auth_clients},
    {'t', opt_time}
  };

static t_opts	*aff_usage_(char *name)
{
  fprintf(stderr, "%s -p port [-x map_x] [-y map_y] "
	  "-n team1 team2 ... [-c auth_clients] [-t time]\n", name);
  return (NULL);
}

static t_opts	*check_options_(t_opts *op, char *name)
{
  if (op->port <= 0 || op->map_x <= 0 || op->map_y <= 0
      || !op->teams || op->auth_clients <= 0 || op->time <= 0)
    {
      aff_usage_(name);
      return (NULL);
    }
  return (op);
}

static void	handle_default_values_(t_opts *op)
{
  if (!op->map_x)
    op->map_x = 10;
  if (!op->map_y)
    op->map_y = 10;
  if (!op->time)
    op->time = 100;
  if (!op->auth_clients)
    op->auth_clients = 20;
}

t_opts		*get_opts(int ac, char **av)
{
  t_opts	*op;
  int		i;
  unsigned 	j;

  i = 1;
  if ((op = calloc(1, sizeof(*op))) == NULL)
    return (NULL);
  while (i < ac)
    {
      if (av[i][0] == '-')
	{
	  j = 0;
	  while (j < sizeof(gl_f) / sizeof(*gl_f))
	    {
	      if (gl_f[j].opt == av[i][1] && gl_f[j].fct(ac, av, i, op) == -1)
		return (aff_usage_(av[0]));
	      ++j;
	    }
	}
      ++i;
    }
  handle_default_values_(op);
  return (check_options_(op, av[0]));
}
