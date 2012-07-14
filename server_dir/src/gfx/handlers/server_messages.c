/*
** server_messages.c for zappy in /home/jorge_d/svn/zappy/server_dir/src/gfx/handlers
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 19:49:11 2011 dimitri jorge
** Last update Thu Jun 23 20:26:56 2011 dimitri jorge
*/

#include <stdio.h>
#include "zappy.h"
#include "gfx.h"

void		gfx_server_msg(t_ctrl *c, char *msg)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	smg(l, msg);
      l = l->next;
    }
}

void		gfx_send_frame_content(t_ctrl *c, int x, int y)
{
  t_jm_list	*l;

  l = c->l;
  while (l)
    {
      if (l->fd != -1 && l->data && ((t_handler *)l->data)->t == GFX)
	bct(c, l, x, y);
      l = l->next;
    }
}

void	suc(t_jm_list *l)
{
  jm_writeln(l, "suc");
}

void	sbp(t_jm_list *l)
{
  jm_writeln(l, "sbp");
}

