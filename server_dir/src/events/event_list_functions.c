/*
** event_list_functions.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 15 19:35:57 2011 dimitri jorge
** Last update Thu Jun 23 18:39:13 2011 dimitri jorge
*/

#include <sys/time.h>
#include <stdlib.h>
#include <math.h>
#include "zappy.h"

void	free_events(t_event *e)
{
  if (e)
    {
      free_events(e->next);
      free(e->param);
      free(e);
    }
}

void	reset_time_in_node(t_event *n, struct timeval *new)
{
  n->start_time = *new;
}

static int	_init_node(t_event *n)
{
  if (gettimeofday(&n->start_time, NULL) == -1)
    {
      free(n);
      return (0);
    }
  return (1);
}

int		push_event(t_event **begin, e_event t, char *s, double d)
{
  t_event	*new;
  t_event	*tmp;

  if (!(new = malloc(sizeof(*new))) || !_init_node(new))
    return (0);
  tmp = *begin;
  new->type = t;
  new->duration = d;
  new->param = s;
  new->next = NULL;
  if (!tmp)
    *begin = new;
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
    }
  return (1);
}
