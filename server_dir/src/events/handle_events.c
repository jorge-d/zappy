/*
** handle_events.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Thu Jun 16 18:38:33 2011 jose rodrigues
** Last update Thu Jul  7 16:47:45 2011 dimitri jorge
*/

#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "gfx.h"
#include "zappy.h"
#include "options.h"

static t_ev_funcs		gl_funcs[] =
  {
    {AVANCE, avance},
    {DROITE, droite},
    {GAUCHE, gauche},
    {VOIR, voir},
    {INVENTAIRE, inventaire},
    {PREND, prend},
    {POSE, pose},
    {EXPULSE, expulse},
    {BROADCAST, broadcast},
    {INCANTATION, incantation},
    {FORK, fork_z},
    {CONNECT_NBR, connect_nbr}
  };

static void	exec_event_(t_ctrl *c, t_jm_list *cli,
			    t_player *p, struct timeval *r)
{
  unsigned	i;
  t_event	*event;

  i = 0;
  while (i < sizeof(gl_funcs) / sizeof(*gl_funcs))
    {
      if (gl_funcs[i].ev == p->e->type && gl_funcs[i].fct)
	gl_funcs[i].fct(c, cli, p);
      ++i;
    }
  event = p->e;
  if ((p->e = p->e->next))
    reset_time_in_node(p->e, r);
  if (event->param)
    free(event->param);
  free(event);
}

static t_event	*_begin_special(t_ctrl *c, t_player *p, enum e_event e)
{
  t_event	*event;

  if (e == FORK || can_elevate(c, p))
    {
      if (e == FORK)
	gfx_player_has_fork(c, p);
      else
	{
	  jm_writeln(p->fd, "elevation en cours");
	  printf(GREEN"#%d starts incantation in (%d, %d)"END, p->id, p->x, p->y);
	  gfx_player_begin_incantation(c, p);
	}
      free(p->e->param);
      p->e->param = NULL;
      return (p->e);
    }
  printf(RED"#%d cannot start incantation in (%d, %d)"END, p->id, p->x, p->y);
  jm_writeln(p->fd, "ko");
  event = p->e;
  p->e = p->e->next;
  free(event->param);
  free(event);
  return (p->e);
}

static void		_poll_events(t_ctrl *c, t_jm_list *l,
				     t_player *p, struct timeval *a)
{
  struct timeval	res;
  struct timeval	duration;
  struct timeval	tmp;
  double		val;

  while (p->e)
    {
      if ((p->e->type == INCANTATION || p->e->type == FORK) &&
	  p->e->param && !_begin_special(c, p, p->e->type))
	return ;
      val = p->e->duration / (double)c->options->time;
      duration.tv_sec = (int)val;
      duration.tv_usec = (val - (int)val) * 1000000;
      timeradd(&p->e->start_time, &duration, &res);
      if (timercmp(&res, a, <=))
	exec_event_(c, l, p, &res);
      else
	{
	  timersub(&res, a, &tmp);
	  if (timercmp(&tmp, &c->delay, <=))
	    c->delay = tmp;
	  return ;
	}
    }
}

void			handle_events(t_ctrl *c)
{
  struct timeval	actual;
  t_jm_list		*tmp;
  t_handler		*h;

  if (gettimeofday(&actual, NULL) != -1)
    {
      tmp = c->l;
      while (tmp)
	{
	  h = tmp->data;
	  if (tmp->type != SERVER && h && h->p && ((t_player *)h->p)->e)
	    _poll_events(c, tmp, (t_player *)h->p, &actual);
	  tmp = tmp->next;
	}
    }
  else
    perror("gettimeofday");
}
