/*
** jm_free_functions.c for network in /home/jorge_d/svn/zappy/networklib
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Fri Jun 10 23:32:42 2011 dimitri jorge
** Last update Mon Jun 27 15:34:25 2011 dimitri jorge
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "jm_network.h"

void	jm_free_socket(t_jm_sock *s)
{
  if (s)
    {
      if (s->socket != -1 && close(s->socket) == -1)
	perror("close");
      free(s);
    }
}

void	jm_free_writebuff(t_writelist *b)
{
  if (b)
    {
      jm_free_writebuff(b->next);
      free(b);
    }
}

void		jm_free_list(t_jm_list *p)
{
  t_jm_list	*tmp;

  while (p)
    {
      tmp = p;
      p = p->next;
      if (tmp->fd != -1 && close(tmp->fd) == -1)
	perror("close");
      if (tmp->buffwrite)
	jm_free_writebuff(tmp->buffwrite);
      free(tmp->s);
      free(tmp);
    }
}

void		jm_remove_from_list(t_jm_list **begin, t_jm_list *e)
{
  t_jm_list	*prev;
  t_jm_list	*next;

  if (!(*begin) || !e)
    return ;
  if (e->fd != -1 && close(e->fd) == -1)
    perror("close");
  prev = e->prev;
  next = e->next;
  if (!prev)
    {
      if (next)
	next->prev = NULL;
      *begin = next;
    }
  else if (!next)
    prev->next = NULL;
  else
    {
      prev->next = next;
      next->prev = prev;
    }
  jm_free_writebuff(e->buffwrite);
  free(e->s);
  free(e);
}
