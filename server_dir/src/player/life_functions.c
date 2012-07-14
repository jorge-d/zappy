/*
** life_functions.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Fri Jun 17 14:11:50 2011 dimitri jorge
** Last update Fri Jun 24 15:55:05 2011 dimitri jorge
*/

#include <sys/time.h>
#include <stdlib.h>
#include "zappy.h"
#include "options.h"

int			_init_lifetime(t_ctrl *c, t_life *n)
{
  struct timeval	duration;
  struct timeval	death;
  double		val;

  if (gettimeofday(&n->start_time, NULL) == -1)
    return (0);
  val = (126.0f / (double)c->options->time) * 10.0f;
  duration.tv_sec = (int)val;
  duration.tv_usec = (val - (int)val) * 1000000;
  timeradd(&duration, &n->start_time, &death);
  if (timercmp(&death, &c->delay, <=))
    c->delay = death;
  return (1);
}

static void	_pop_node(t_ctrl *c, t_life *node)
{
  t_life	*prev;
  t_life	*next;

  prev = node->prev;
  next = node->next;
  if (!prev)
    {
      if (next)
	next->prev = NULL;
      c->life = next;
    }
  else if (!next)
    prev->next = NULL;
  else
    {
      prev->next = next;
      next->prev = prev;
    }
  free(node);
}

void		remove_life_node(t_ctrl *c, t_player *p)
{
  t_life	*tmp;

  tmp = c->life;
  while (tmp)
    {
      if (tmp->p == p)
	{
	  _pop_node(c, tmp);
	  return ;
	}
      tmp = tmp->next;
    }
}

int		push_life(t_ctrl *c, t_player *p)
{
  t_life	*new;
  t_life	*tmp;

  if (!(new = malloc(sizeof(*new))) || !_init_lifetime(c, new))
    return (0);
  new->p = p;
  new->next = NULL;
  new->prev = NULL;
  tmp = c->life;
  if (tmp)
    {
      tmp->prev = new;
      new->next = tmp;
    }
  c->life = new;
  return (1);

}
