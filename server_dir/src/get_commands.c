/*
** get_commands.c for zappy in /home/jorge_d/svn/zappy/server_dir/src
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Sun Jun 19 18:55:59 2011 dimitri jorge
** Last update Thu Jul  7 16:54:28 2011 dimitri jorge
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"

static int	_event_list_size(t_event *e)
{
  int		nb;

  nb = 0;
  while (e)
    {
      nb++;
      e = e->next;
    }
  return (nb);
}

void		get_commands(t_ctrl *c, t_jm_list *tmp)
{
  char		*s;
  int		nb;
  t_handler	*h;

  nb = 0;
  h = (t_handler *)tmp->data;
  if (h->t == IA && h->p && ((t_player *)h->p)->e)
    nb = _event_list_size(((t_player *)h->p)->e);
  while ((s = jm_get_msg(tmp)))
    {
      if (h && h->handler && nb < 10)
	{
	  h->handler(c, tmp, s);
	  nb++;
	}
      else if (nb >= 10)
	printf(RED"Flood protection: ignoring '%s'"END, s);
      free(s);
    }
}
