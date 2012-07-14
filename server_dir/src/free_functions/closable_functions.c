/*
** closable_functions.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 15 18:42:55 2011 dimitri jorge
** Last update Sun Jul 10 19:02:14 2011 jose rodrigues
*/

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include "zappy.h"
#include "event.h"
#include "options.h"

int		push_closable(t_closable **begin, t_jm_list *t)
{
  t_closable	*new;

  if (!(new = calloc(1, sizeof(*new))))
    return (-1);
  new->p = t;
  new->next = *begin;
  *begin = new;
  return (1);
}

void	free_closable(t_closable *t)
{
  if (t)
    {
      free_closable(t->next);
      free(t);
    }
}

static void	_destroy_closable(t_ctrl *c, t_closable *tmp)
{
  if (tmp)
    {
      _destroy_closable(c, tmp->next);
      if (tmp->p->data && ((t_handler *)tmp->p->data)->t == IA)
	remove_player(c, (t_player *)((t_handler *)tmp->p->data)->p);
      if (tmp->p->fd != -1 && close(tmp->p->fd) == -1)
	perror("close");
      free(((t_handler *)tmp->p->data));
      tmp->p->fd = -1;
      jm_remove_from_list(&c->l, tmp->p);
      free(tmp);
    }
}

void		handle_closable(t_ctrl *c)
{
  if (c->to_close)
    {
      _destroy_closable(c, c->to_close);
      c->to_close = NULL;
    }
}
