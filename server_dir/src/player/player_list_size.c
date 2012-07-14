/*
** player_list_size.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 15 17:43:31 2011 dimitri jorge
** Last update Mon Jun 20 14:08:08 2011 dimitri jorge
*/

#include "zappy.h"

int		player_list_size(t_team *t)
{
  int		nb;
  t_player	*p;

  p = t->players;
  nb = 0;
  while (p)
    {
      if (p->fd->fd != -1)
	nb++;
      p = p->next;
    }
  return (nb);
}

