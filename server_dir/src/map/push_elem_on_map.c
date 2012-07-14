/*
** set_player_on_map.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Thu Jun 16 17:16:23 2011 dimitri jorge
** Last update Mon Jun 27 16:26:00 2011 dimitri jorge
*/

#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"

int		push_elem_on_map(t_ctrl *c, void *p, int x, int y,
				 e_elem t)
{
  t_frame	*new;

  if (!(new = calloc(1, sizeof(*new))))
    {
      perror("calloc");
      return (-1);
    }
  new->type = t;
  new->p = p;
  new->next = NULL;
  new->prev = NULL;
  set_elem_on_map(c, new, x, y);
  return (0);
}
