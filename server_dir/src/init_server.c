/*
** init_server.c for zappy in /home/rodrig_d/rendu/c/zappy/server
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Mon Jun 13 16:30:17 2011 jose rodrigues
** Last update Thu Jul  7 16:04:08 2011 dimitri jorge
*/

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"

static void	_init_struct(t_ctrl *c, t_opts *o)
{
  c->id_player = 1;
  c->options = o;
  c->teams = o->teams;
  c->l = NULL;
  c->to_close = NULL;
  c->flag = 1;
  c->life = NULL;
  c->eggs = NULL;
  c->delay.tv_sec = 3600;
  c->delay.tv_usec = 0;
}

t_ctrl		*init_server(int ac, char **av)
{
  t_opts	*o;
  t_ctrl	*c;

  if ((o = get_opts(ac, av)) == NULL)
    return (NULL);
  if (!(c = calloc(1, sizeof(*c))) ||
      !(c->map = calloc(o->map_x * o->map_y, sizeof(*c->map))))
    {
      perror("calloc");
      return (NULL);
    }
  srand(time(NULL));
  _init_struct(c, o);
  if (!jm_init_server(&c->l, o->port, 30))
    {
      printf(RED"Error starting server in lib!"END);
      free_options(o);
      free(c);
      return (NULL);
    }
  printf(GREEN"Server started!"END);
  return (c);
}
