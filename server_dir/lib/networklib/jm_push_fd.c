/*
** put_fd_in_list.c for networklib in /home/jorge_d/svn/zappy/networklib
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Fri Jun 10 23:14:11 2011 dimitri jorge
** Last update Sun Jun 26 23:39:49 2011 dimitri jorge
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "jm_network.h"

static void	_init_circular_list(t_circular *p)
{
  memset(p->buff, 0, sizeof(p->buff));
  p->rdidx = 0;
  p->wridx = 0;
}

int		jm_push_fd(t_jm_list **b, t_jm_sock *s, int fd, jm_type t)
{
  t_jm_list	*new;
  t_jm_list	*tmp;

  if (!(new = calloc(1, sizeof(*new))))
    return (0);
  new->fd = fd;
  new->flag = 0;
  new->type = t;
  new->s = s;
  _init_circular_list(&new->buffread);
  new->buffwrite = NULL;
  new->data = NULL;
  new->next = NULL;
  new->prev = NULL;
  if ((tmp = *b))
    {
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
      new->prev = tmp;
    }
  else
    *b = new;
  return (1);
}
