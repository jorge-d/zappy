/*
** avance.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Fri Jun 17 14:04:29 2011 jose rodrigues
** Last update Thu Jul  7 16:46:57 2011 dimitri jorge
*/

#include <stdio.h>
#include "zappy.h"
#include "options.h"
#include "event.h"
#include "gfx.h"

t_incant	gl_inc[] =
  {
    {0, 0, 0, 0, 0, 0, 0, 0},
    {1, 1, 1, 0, 0, 0, 0, 0},
    {2, 2, 1, 1, 1, 0, 0, 0},
    {3, 2, 2, 0, 1, 0, 2, 0},
    {4, 4, 1, 1, 2, 0, 1, 0},
    {5, 4, 1, 2, 1, 3, 0, 0},
    {6, 6, 1, 2, 3, 0, 1, 0},
    {7, 6, 2, 2, 2, 2, 2, 1}
  };

int	can_elevate(t_ctrl *c, t_player *p)
{
  int	idx;

  idx = p->lvl;
  if (idx >= 8)
    return (0);
  if (get_nb_object(c, p->x, p->y, LINEMATE) != gl_inc[idx].linemate ||
      get_nb_object(c, p->x, p->y, DERAUMERE) != gl_inc[idx].deraumere ||
      get_nb_object(c, p->x, p->y, SIBUR) != gl_inc[idx].sibur ||
      get_nb_object(c, p->x, p->y, MENDIANE) != gl_inc[idx].mendiane ||
      get_nb_object(c, p->x, p->y, PHIRAS) != gl_inc[idx].phiras ||
      get_nb_object(c, p->x, p->y, THYSTAME) != gl_inc[idx].thystame)
    return (0);
  if (get_nb_object(c, p->x, p->y, PLAYER) != gl_inc[idx].players)
    return (0);
  if (get_nb_players(c, p->x, p->y, p->lvl) != gl_inc[idx].players)
    return (0);
  return (1);
}

int	incantation(t_ctrl *c, t_jm_list *cli, t_player *p)
{
  printf(GREEN"Player %d wants to incantate"END, p->id);
  if (!can_elevate(c, p))
    {
      jm_writeln(cli, "ko");
      gfx_player_end_incantation(c, p, 0);
    }
  else
    {
      elevate_players(c, p->x, p->y, p->lvl);
      gfx_player_end_incantation(c, p, 1);
      dispatch_elems(c, p->x, p->y);
    }
  return (0);
}
