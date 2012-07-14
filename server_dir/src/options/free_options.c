/*
** free_options.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Wed Jun 15 15:36:54 2011 jose rodrigues
** Last update Wed Jun 15 15:50:40 2011 jose rodrigues
*/

#include <stdlib.h>
#include "options.h"

static void	free_teams_(t_team *t)
{
  if (t)
    {
      free_teams_(t->next);
      free(t);
    }
}

void		free_options(t_opts *o)
{
  free_teams_(o->teams);
  free(o);
}
