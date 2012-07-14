/*
** create_player.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Thu Jun 16 15:43:35 2011 dimitri jorge
** Last update Sun Jul 10 20:44:47 2011 jose rodrigues
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "zappy.h"
#include "options.h"

static t_player	*_init_new_player(t_ctrl *c, t_team *t,
				  t_jm_list *fd, int id)
{
  t_player	*new;

  if (!(new = calloc(1, sizeof(*new))) || !push_life(c, new))
    return (NULL);
  new->id = id;
  new->food = 10;
  new->lvl = 1;
  new->fd = fd;
  new->x = rand() % c->options->map_x;
  new->y = rand() % c->options->map_y;
  new->d = rand() % 4;
  new->t = t;
  memset(&new->inventory, 0, sizeof(new->inventory));
  new->e = NULL;
  return new;
}

t_player	*create_player(t_ctrl *c, t_team *t, t_jm_list *fd, int id)
{
  t_player	*new;
  t_player	*tmp;

  if (!(new = _init_new_player(c, t, fd, id)) ||
      (push_elem_on_map(c, new, new->x, new->y, PLAYER) == -1))
    return (NULL);
  tmp = t->players;
  new->next = NULL;
  new->prev = NULL;
  if (!tmp)
    t->players = new;
  else
    {
      while (tmp->next)
	tmp = tmp->next;
      tmp->next = new;
      new->prev = tmp;
    }
  return (new);
}
