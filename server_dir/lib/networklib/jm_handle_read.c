/*
** jm_handle_read.c for networklib in /home/jorge_d/svn/zappy/networklib
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Sun Jun 12 17:01:32 2011 dimitri jorge
** Last update Thu Jul  7 16:08:44 2011 dimitri jorge
*/

#include <sys/select.h>
#include <sys/types.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "jm_network.h"
#include "color.h"

static char	*_get_msg(t_circular *tmp)
{
  int		i;
  int		c;
  char		buff[BUFFSIZE + 1];

  i = tmp->rdidx;
  c = 0;
  memset(buff, 0, sizeof(buff));
  while (i != tmp->wridx)
    {
      if (tmp->buff[i] == '\n' || tmp->buff[i] == '\r')
	buff[c++] = 0;
      else
	buff[c++] = tmp->buff[i];
      if (tmp->buff[i] == '\n')
	{
	  i++;
	  tmp->rdidx = i % BUFFSIZE;
	  return (!strlen(buff) ? NULL : strdup(buff));
	}
      if (++i >= BUFFSIZE)
	i %= BUFFSIZE;
    }
  return (NULL);
}

char		*jm_get_msg(t_jm_list *tmp)
{
  t_circular	*t;

  t = &tmp->buffread;
  if (tmp->fd == -1 || t->rdidx == t->wridx)
    return (NULL);
  if (!t->buff[t->rdidx])
    {
      t->rdidx++;
      if (t->rdidx >= BUFFSIZE)
	t->rdidx %= BUFFSIZE;
    }
  return (_get_msg(t));
}

static void	_add_char(t_circular *tmp, char c)
{
  tmp->buff[tmp->wridx] = c;
  if (++tmp->wridx >= BUFFSIZE)
    tmp->wridx %= BUFFSIZE;
  if (tmp->wridx == tmp->rdidx)
    {
      tmp->rdidx++;
      tmp->rdidx %= BUFFSIZE;
    }
}

void	jm_handle_read(t_jm_list *tmp)
{
  char	buff[RDBLOCK + 1];
  int	rd;
  int	i;

  if (tmp->fd == -1)
    return ;
  i = 0;
  if ((rd = read(tmp->fd, buff, RDBLOCK)) > 0)
    {
      while (i < rd)
	{
	  if (buff[i] == '\n' && i > 0 && buff[i - 1] == '\r')
	    tmp->flag = 1;
	  _add_char(&tmp->buffread, buff[i++]);
	}
      return ;
    }
  else if (rd == -1)
    perror("read");
  else
    fprintf(stderr, RED"Client <%s> disconnected!"END,
	    inet_ntoa(tmp->s->bind.sin_addr));
  if (close(tmp->fd) == -1)
    perror("close");
  tmp->fd = -1;
}
