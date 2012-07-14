/*
** get_nb_object.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Sun Jun 19 19:40:47 2011 dimitri jorge
** Last update Thu Jun 23 17:39:45 2011 dimitri jorge
*/

#include <stdio.h>
#include "zappy.h"
#include "options.h"

int		get_nb_object(t_ctrl *c, int x, int y, e_elem e)
{
  t_frame	*f;
  int		nb;

  nb = 0;
  f = getframe(c, x, y);
  while (f)
    {
      if (f->type == e)
	nb++;
      f = f->next;
    }
  return (nb);
}

int		get_nb_players(t_ctrl *c, int x, int y, int lvl)
{
  t_frame	*f;
  int		nb;

  nb = 0;
  f = getframe(c, x, y);
  while (f)
    {
      if (f->type == PLAYER && f->p && ((t_player *)f->p)->lvl == lvl)
	nb++;
      f = f->next;
    }
  return (nb);
}
