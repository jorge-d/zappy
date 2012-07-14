/*
** get_nb_elems.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Thu Jun 23 10:00:15 2011 jose rodrigues
** Last update Sun Jul 10 14:29:48 2011 jose rodrigues
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "zappy.h"
#include "options.h"

extern t_incant gl_inc[];

static t_incant	*get_incant_(int lvl)
{
  int		i;

  i = 0;
  while (i < 8)
    {
      if (gl_inc[i].lvl == lvl)
	return (gl_inc + i);
      ++i;
    }
  return (gl_inc);
}

static void	update_res_(t_player *p, int *t)
{
  t_incant	*g;

  g = get_incant_(p->lvl);
  t[LINEMATE] += g->linemate * 30;
  t[DERAUMERE] += g->deraumere * 30;
  t[SIBUR] += g->sibur * 30;
  t[MENDIANE] += g->mendiane * 30;
  t[PHIRAS] += g->phiras * 30;
  t[THYSTAME] += g->thystame * 30;
}

void		get_nb_elems(t_ctrl *c, int t[ALL])
{
  t_jm_list	*tmp;
  int		i;

  i = 0;
  tmp = c->l;
  t[LINEMATE] = (getmapx(c) *  getmapy(c)) / 5;
  t[DERAUMERE] = (getmapx(c) *  getmapy(c)) / 5;
  t[SIBUR] = (getmapx(c) *  getmapy(c)) / 5;
  t[MENDIANE] = (getmapx(c) *  getmapy(c)) / 5;
  t[PHIRAS] = (getmapx(c) *  getmapy(c)) / 5;
  t[THYSTAME] = (getmapx(c) *  getmapy(c)) / 5;
  while (tmp)
    {
      if (tmp->fd != -1 && (t_handler *)tmp->data
	  && ((t_handler *)tmp->data)->t == IA && ((t_handler *)tmp->data)->p)
	{
	  t[NOURRITURE] += (getmapx(c) *  getmapy(c)) / 6;
	  update_res_(((t_player *)((t_handler *)tmp->data)->p), t);
	}
      tmp = tmp->next;
    }
}
