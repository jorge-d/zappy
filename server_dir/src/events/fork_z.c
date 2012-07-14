/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Thu Jul  7 16:48:29 2011 dimitri jorge
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

static void	_push_egg(t_ctrl *c, t_eclode *new)
{
  t_eclode	*tmp;

  tmp = c->eggs;
  if (!tmp)
    c->eggs = new;
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      new->prev = tmp;
      tmp->next = new;
    }
}

int		fork_z(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  t_eclode	*new;

  printf(GREEN"Player %d is forking"END, p->id);
  if ((new = malloc(sizeof(*new))))
    {
      bzero(new, sizeof(*new));
      if (gettimeofday(&new->start_time, NULL) == -1)
	{
	  perror("gettimeofday");
	  free(new);
	  return (0);
	}
      new->x = p->x;
      new->y = p->y;
      new->t = p->t;
      new->id_parent = p->id;
      new->id = c->id_player++;
      new->duration = 600.0f;
      _push_egg(c, new);
      jm_writeln(cli, "ok");
      gfx_player_fork_end(c, p, new);
    }
  else
    perror("malloc");
  return (0);
}
