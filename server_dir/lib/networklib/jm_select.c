/*
** jm_select.c for network in /home/jorge_d/svn/zappy/networklib
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Fri Jun 10 23:56:34 2011 dimitri jorge
** Last update Tue Jul  5 12:25:49 2011 dimitri jorge
*/

#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "jm_network.h"

static int	_set_fds(t_jm_list *tmp, fd_set *read, fd_set *write)
{
  int		nb;

  nb = -1;
  FD_ZERO(read);
  FD_ZERO(write);
  while (tmp)
    {
      if (tmp->fd != -1)
	{
	  if (tmp->type == READ || tmp->type == RDWR || tmp->type == SERVER)
	    FD_SET(tmp->fd, read);
	  if ((tmp->type == WRITE || tmp->type == RDWR) && tmp->buffwrite)
	    FD_SET(tmp->fd, write);
	  nb = (tmp->fd > nb ? tmp->fd : nb);
	}
      tmp = tmp->next;
    }
  return (nb);
}

static void	_handle_it(t_jm_list **begin, fd_set *read, fd_set *write)
{
  t_jm_list	*tmp;

  tmp = *begin;
  while (tmp)
    {
      if (tmp->fd != -1)
	{
	  if (tmp->type == SERVER && FD_ISSET(tmp->fd, read))
	    jm_add_client(begin, tmp);
	  if (tmp->type == RDWR && FD_ISSET(tmp->fd, read))
	    jm_handle_read(tmp);
	  if (tmp->type == RDWR && FD_ISSET(tmp->fd, write))
	    jm_handle_write(tmp);
	}
      tmp = tmp->next;
    }
}

void		jm_select(t_jm_list **begin, struct timeval *tv)
{
  fd_set	read;
  fd_set	write;
  int		max;
  int		val;

  if ((max = _set_fds(*begin, &read, &write)) != -1)
    {
      if ((val = select(max + 1, &read, &write, NULL, tv)) > 0)
	_handle_it(begin, &read, &write);
      else if (val == -1)
	perror("select");
    }
  tv->tv_sec = 999;
  tv->tv_usec = 0;
}
