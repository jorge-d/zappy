/*
** get_player_from_id.c for zappy in /home/jorge_d/svn/zappy/server_dir/src
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 17:04:50 2011 dimitri jorge
** Last update Wed Jun 22 17:05:37 2011 dimitri jorge
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "zappy.h"
#include "options.h"

t_player	*get_player_from_id(t_ctrl *c, int id)
{
  t_team	*t;
  t_player	*p;

  t = c->teams;
  while (t)
    {
      p = t->players;
      while (p)
	{
	  if (p->id == id)
	    return (p);
	  p = p->next;
	}
      t = t->next;
    }
  return (NULL);
}

