/*
** start_zappy.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Wed Jun 15 16:07:08 2011 jose rodrigues
** Last update Sun Jul 10 20:02:51 2011 jose rodrigues
*/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "zappy.h"

static void	_init_handler(t_jm_list *tmp)
{
  if (!(tmp->data = calloc(1, sizeof(t_handler))))
    {
      perror("calloc");
      if (close(tmp->fd) == -1)
	perror("close");
      tmp->fd = -1;
    }
  else
    {
      jm_writeln(tmp, "BIENVENUE");
      ((t_handler *)tmp->data)->t = UNDEFINED;
      ((t_handler *)tmp->data)->p = NULL;
      ((t_handler *)tmp->data)->handler = handle_type;
    }
}

static t_jm_list	*_handle_disconnected(t_ctrl *c, t_jm_list *tmp)
{
  t_jm_list		*next;

  free(tmp->data);
  next = tmp->next;
  jm_remove_from_list(&c->l, tmp);
  return (next);
}

static void	_handle_fds(t_ctrl *c)
{
  t_jm_list	*tmp;
  int		flag;

  tmp = c->l;
  while (tmp)
    {
      flag = 1;
      if (tmp->type != SERVER)
	{
 	  if (tmp->fd != - 1 && tmp->data == NULL)
	    _init_handler(tmp);
	  if (tmp->fd != -1)
	    get_commands(c, tmp);
 	  else if (!tmp->data)
	    {
	      tmp = _handle_disconnected(c, tmp);
	      flag = 0;
	    }
	}
      if (flag == 1)
	tmp = tmp->next;
    }
}

int	start_zappy(t_ctrl *c)
{
  while (c->flag)
    {
      jm_select(&c->l, &c->delay);
      handle_closable(c);
      handle_life(c, c->life);
      _handle_fds(c);
      handle_events(c);
      generate_elems(c);
      handle_eclosion(c, c->eggs);
    }
  return (0);
}
