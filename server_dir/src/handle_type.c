/*
** handle_type.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Wed Jun 15 16:57:58 2011 jose rodrigues
** Last update Thu Jul  7 15:44:28 2011 dimitri jorge
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include "options.h"
#include "zappy.h"
#include "gfx.h"

static int	handle_graphic_(t_ctrl *c, t_jm_list *cli)
{
  ((t_handler*)cli->data)->t = GFX;
  ((t_handler*)cli->data)->handler = handle_gfx;
  msz(c, cli);
  sgt(c, cli);
  mct(c, cli);
  tna(c, cli);
  list_eggs_and_players(c, cli);
  return (1);
}

static int	_insert_in_game(t_ctrl *c, t_jm_list *cli, t_team *t, int nb)
{
  char		buff[256];

  if (!attribute_player(c, cli, t))
    return (0);
  ((t_handler*)cli->data)->handler = handle_commands;
  snprintf(buff, sizeof(buff) - 1, "%d\n%d %d", nb, getmapx(c), getmapy(c));
  jm_writeln(cli, buff);
  return (1);

}

static int	handle_teamname_(t_ctrl *c, t_jm_list *cli, char *s)
{
  t_team	*t;
  int		nb;

  t = c->teams;
  ((t_handler*)cli->data)->t = UNDEFINED;
  ((t_handler*)cli->data)->handler = NULL;
  while (t)
    {
      if (!strcmp(s, t->name))
	{
	  nb = (c->options->auth_clients + t->nb_fork) - player_list_size(t);
	  if (nb > 0)
	    return (_insert_in_game(c, cli, t, nb));
	}
      t = t->next;
    }
  jm_writeln(cli, "ko");
  if (!push_closable(&c->to_close, cli))
    return (0);
  return (1);
}

int		handle_type(t_ctrl *c, t_jm_list *cli, char *s)
{
  if (!strcmp(s, "GRAPHIC"))
    handle_graphic_(c, cli);
  else if (!handle_teamname_(c, cli, s))
    {
      if (cli->fd != -1 && close(cli->fd) == -1)
      	perror("close");
      cli->fd = -1;
      free(cli->data);
      cli->data = NULL;
    }
  return (0);
}
