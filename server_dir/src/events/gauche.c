/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Thu Jul  7 16:49:23 2011 dimitri jorge
*/

#include <stdio.h>
#include "zappy.h"
#include "gfx.h"

int	gauche(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  p->d = (p->d + 1) % 4;
  gfx_player_moves(c, p);
  jm_writeln(cli, "ok");
  printf(GREEN"Player %d (%d, %d) is turning left"END, p->id, p->x, p->y);
  return (0);
}
