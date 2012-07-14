/*
** handle_life.c for zappy in /home/jorge_d/svn/zappy/server_dir/src
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Mon Jun 20 14:39:04 2011 dimitri jorge
** Last update Thu Jul  7 16:18:43 2011 dimitri jorge
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

static void	_kill_player(t_ctrl *c, t_life *n)
{
  jm_writeln(n->p->fd, "mort");
  if (n->p->fd->s)
    {
      gfx_player_is_dead(c, n->p);
      printf(CYAN"Player #%d died"END, n->p->id);
    }
  else
    {
      gfx_egg_died(c, n->p);
      printf(YELLOW"Ecloded egg #%d died"END, n->p->id);
    }
  push_closable(&c->to_close, n->p->fd);
}

static void		_decrement_life(t_ctrl *c, t_life *n, struct timeval *a)
{
  struct timeval	duration;
  struct timeval	tmp;
  double		val;

  val = 126.0f / (double)c->options->time;
  duration.tv_sec = (int)val;
  duration.tv_usec = (val - (int)val) * 1000000;
  timeradd(&duration, &n->start_time, &tmp);
  while (timercmp(&tmp, a, <=))
    {
      n->p->food--;
      if (n->p->food < 0)
	{
	  _kill_player(c, n);
	  return ;
	}
      timeradd(&n->start_time, &duration, &n->start_time);
      timeradd(&duration, &n->start_time, &tmp);
    }
}

static void		_calc_death(t_ctrl *c, t_life *tmp, struct timeval *a)
{
  struct timeval	duration;
  struct timeval	tmp2;
  struct timeval	death;
  double		val;

  val = (126.0f / (double)c->options->time) * (tmp->p->food + 1);
  duration.tv_sec = (int)val;
  duration.tv_usec = (val - (int)val) * 1000000;
  timeradd(&duration, &tmp->start_time, &death);
  timeradd(&c->delay, a, &tmp2);
  timersub(&death, a, &duration);
  if (timercmp(&death, &tmp2, <=))
    c->delay = duration;
}

void			handle_life(t_ctrl *c, t_life *tmp)
{
  struct timeval	actual;

  if (gettimeofday(&actual, NULL) != -1)
    while (tmp)
      {
	_decrement_life(c, tmp, &actual);
	if (tmp->p->food >= 0)
	  _calc_death(c, tmp, &actual);
	tmp = tmp->next;
      }
  else
    perror("gettimeofday");
}
