/*
** free_control.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Mon Jun 20 19:33:26 2011 dimitri jorge
** Last update Sun Jul 10 17:28:49 2011 jose rodrigues
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"

static void	free_handlers(t_jm_list *tmp)
{
  t_handler	*h;
  t_player	*p;

  while (tmp)
    {
      if (tmp->data)
	{
	  h = tmp->data;
	  if ((p = h->p))
	    free_events(p->e);
	  free(tmp->data);
	}
      tmp = tmp->next;
    }
}

static void	free_map(t_ctrl *c)
{
  int		i;
  int		j;
  t_frame	*tmp;
  t_frame	*save;

  i = 0;
  while (i < getmapy(c))
    {
      j = 0;
      while (j < getmapx(c))
	{
	  if ((tmp = getframe(c, j, i)))
	    while (tmp)
	      {
		save = tmp;
		tmp = tmp->next;
		if (save->type == PLAYER)
		  free(save->p);
		free(save);
	      }
	  j++;
	}
      i++;
    }
}

static void	free_life(t_life *t)
{
  t_life	*tmp;

  while (t)
    {
      tmp = t;
      t = t->next;
      free(tmp);
    }
}

static void	free_eggs(t_eclode *t)
{
  t_eclode	*tmp;

  while (t)
    {
      tmp = t;
      t = t->next;
      free(tmp);
    }
}

void	free_control(t_ctrl *c)
{
  free_handlers(c->l);
  jm_free_list(c->l);
  free_closable(c->to_close);
  free_life(c->life);
  free_eggs(c->eggs);
  free_map(c);
  free_options(c->options);
  free(c->map);
  free(c);
}
