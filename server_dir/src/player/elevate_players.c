/*
** elevate_players.c for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Sun Jun 19 20:00:52 2011 dimitri jorge
** Last update Thu Jul  7 16:25:19 2011 dimitri jorge
*/

#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "gfx.h"

void		elevate_players(t_ctrl *c, int x, int y, int lvl)
{
  t_frame	*f;
  char		buff[64];
  t_player	*p;

  snprintf(buff, sizeof(buff) - 1, "niveau actuel : %d", lvl + 1);
  f = getframe(c, x, y);
  while (f)
    {
      if (f->type == PLAYER && (p = (t_player *)f->p) && p->lvl == lvl)
	{
	  p->lvl++;
	  p->t->nblvlmax++;
	  printf(CYAN"Player #%d is now lvl %d"END, p->id, p->lvl);
	  jm_writeln(p->fd, buff);
	  if (p->lvl >= 8 && p->t->nblvlmax >= 6)
	    {
	      gfx_end_of_game(c, p->t->name);
	      printf(GREEN"Team %s won!"END, p->t->name);
	      c->flag = 0;
	      return ;
	    }
	}
      f = f->next;
    }
}
