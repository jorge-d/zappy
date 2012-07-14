/*
** jm_handle_write.c for network in /home/jorge_d/svn/zappy/networklib
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Sun Jun 12 17:53:54 2011 dimitri jorge
** Last update Thu Jul  7 16:07:08 2011 dimitri jorge
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

void		jm_handle_write(t_jm_list *e)
{
  t_writelist	*tmp;
  int		rd;

  if (!(tmp = e->buffwrite))
    return ;
  while (tmp)
    {
      if (!((rd = write(e->fd, tmp->buff, strlen(tmp->buff))) > 0))
	{
	  if (rd == -1)
	    perror("write");
	  if (e->fd != -1 && close(e->fd) == -1)
	    perror("close");
	  e->fd = -1;
	  jm_free_writebuff(e->buffwrite);
	  e->buffwrite = NULL;
	  return ;
	}
      tmp = tmp->next;
    }
  jm_free_writebuff(e->buffwrite);
  e->buffwrite = NULL;
}

static int	_push_buffwrite(t_writelist **begin)
{
  t_writelist	*new;
  t_writelist	*tmp;

  if ((new = calloc(1, sizeof(*new))))
    {
      new->next = NULL;
      memset(new->buff, 0, sizeof(new->buff));
      tmp = *begin;
      if (!tmp)
	*begin = new;
      else
	{
	  while (tmp->next)
	    tmp = tmp->next;
	  tmp->next = new;
	}
      return (1);
    }
  else
    perror("jm_newtork: calloc");
  return (0);
}

static char	*_fill_buffer(t_writelist *e, char *s)
{
  int           i;

  if (((i = strlen(e->buff)) < BUFFSIZE))
    {
      strncpy(&e->buff[i], s, BUFFSIZE - i);
      return (((BUFFSIZE - i) < (int)strlen(s)) ? &s[(BUFFSIZE - i)] : NULL);
    }
  return (s);

}

/*
** Use the defines instead of the function above
*/

void		jm_push_write(t_jm_list *e, char *buff, int flag)
{
  t_writelist	*tmp;

  if (e->fd == -1 || (!e->buffwrite && !_push_buffwrite(&e->buffwrite)))
    return ;
  tmp = e->buffwrite;
  while (tmp->next)
    tmp = tmp->next;
  while ((buff = _fill_buffer(tmp, buff)))
    {
      if (strlen(tmp->buff) >= BUFFSIZE)
	{
	  if (!_push_buffwrite(&e->buffwrite))
	    {
	      jm_free_writebuff(e->buffwrite);
	      e->buffwrite = NULL;
	      return ;
	    }
	  tmp = tmp->next;
	  if (!tmp)
	    fprintf(stderr, RED"A strange error occured in jm_write"END);
	}
    }
  if (flag != 1)
    return ;
  jm_push_write(e, (e->flag == 0 ? "\n" : "\r\n"), 0);
}
