/*
** generate_elems.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Thu Jun 23 09:58:22 2011 jose rodrigues
** Last update Wed Jul  6 18:16:32 2011 jose rodrigues
*/

#include <stdlib.h>
#include <string.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

static void	equalize_elems_(t_ctrl *c, int *t)
{
  int		i;
  t_frame	*tmp;

  i = 0;
  while (i < (getmapx(c) * getmapy(c)))
    {
      tmp = c->map[i];
      while (tmp)
	{
	  if (tmp->type < PLAYER && t[tmp->type] > 0)
	    t[tmp->type]--;
	  else if (tmp->type == PLAYER && tmp->p)
	    {
	      t[LINEMATE] -= ((t_player *)tmp->p)->inventory.linemate;
	      t[DERAUMERE] -= ((t_player *)tmp->p)->inventory.deraumere;
	      t[SIBUR] -= ((t_player *)tmp->p)->inventory.sibur;
	      t[MENDIANE] -= ((t_player *)tmp->p)->inventory.mendiane;
	      t[PHIRAS] -= ((t_player *)tmp->p)->inventory.phiras;
	      t[THYSTAME] -= ((t_player *)tmp->p)->inventory.thystame;
	    }
	  tmp = tmp->next;
	}
      ++i;
    }
}

int		generate_elems(t_ctrl *c)
{
  int		t[ALL];
  int		i;
  int		x;
  int		y;

  i = 0;
  memset(t, 0, sizeof(t));
  get_nb_elems(c, t);
  equalize_elems_(c, t);
  while (i < PLAYER)
    {
      while (t[i] > 0)
	{
	  x = rand() % getmapx(c);
	  y = rand() % getmapy(c);
	  push_elem_on_map(c, NULL, x, y, i);
	  gfx_send_frame_content(c, x, y);
	  t[i]--;
	}
      ++i;
    }
  return (0);
}
