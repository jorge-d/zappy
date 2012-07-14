/*
** handle_eclosion.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Mon Jun 20 17:02:45 2011 dimitri jorge
** Last update Sun Jul 10 18:26:41 2011 jose rodrigues
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

static t_jm_list	*_create_f(void)
{
  t_jm_list		*f;

  if ((f = calloc(1, sizeof(*f))))
    {
      f->fd = -1;
      f->type = RDWR;
      if (!(f->data = calloc(1, sizeof(t_handler))))
	{
	  free(f);
	  return (NULL);
	}
      ((t_handler *)f->data)->t = IA;
      ((t_handler *)f->data)->handler = handle_commands;
      ((t_handler *)f->data)->p = NULL;
      f->next = NULL;
      f->prev = NULL;
    }
  return (f);
}

static void	_push_fd(t_ctrl *c, t_jm_list *t)
{
  t_jm_list	*tmp;

  tmp = c->l;
  if (!tmp)
    c->l = t;
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = t;
      t->prev = tmp;
    }
}

static void	_pop_egg(t_ctrl *c, t_eclode *tmp)
{
  t_eclode	*next;
  t_eclode	*prev;

  next = tmp->next;
  prev = tmp->prev;
  if (!prev)
    {
      if (next)
	next->prev = NULL;
      c->eggs = next;
    }
  else if (!next)
    prev->next = NULL;
  else
    {
      prev->next = next;
      next->prev = prev;
    }
  free(tmp);
}

static t_eclode	*_eclode(t_ctrl *c, t_eclode *tmp)
{
  t_player	*p;
  t_jm_list	*f;
  t_eclode	*tmp2;

  printf(YELLOW"Ecloding egg #%d"END, tmp->id);
  if (!(f = _create_f()) || !(p = create_player(c, tmp->t, f, tmp->id)))
    {
      fprintf(stderr, RED"Error hatching egg #%d"END, tmp->id);
      free(f);
      return (tmp->next);
    }
  ((t_handler *)f->data)->p = p;
  reset_player_into_map(c, p, tmp->x, tmp->y);
  gfx_egg_hatched(c, tmp);
  p->t->nb_fork++;
  _push_fd(c, f);
  tmp2 = tmp;
  tmp = tmp->next;
  _pop_egg(c, tmp2);
  printf(YELLOW"Egg #%d (team %s) is now grown up in (%d, %d)"
	 END, p->id, p->t->name, p->x, p->y);
  return (tmp);
}

void			handle_eclosion(t_ctrl *c, t_eclode *tmp)
{
  struct timeval	actual;
  struct timeval	res;
  struct timeval	duration;
  double		val;

  if (gettimeofday(&actual, NULL) != -1)
    while (tmp)
      {
  	val = tmp->duration / (double)c->options->time;
  	duration.tv_sec = (int)val;
  	duration.tv_usec = (val - (int)val) * 1000000;
  	timeradd(&tmp->start_time, &duration, &res);
  	if (timercmp(&res, &actual, <=))
  	  tmp = _eclode(c, tmp);
  	else
  	  {
  	    timersub(&res, &actual, &duration);
  	    if (timercmp(&duration, &c->delay, <=))
  	      c->delay = duration;
  	    tmp = tmp->next;
  	  }
      }
}
