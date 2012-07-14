/*
** handle_commands.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Wed Jun 15 16:11:07 2011 jose rodrigues
** Last update Thu Jul  7 16:56:33 2011 dimitri jorge
*/

#include <stdio.h>
#include <string.h>
#include "options.h"
#include "commands.h"
#include "zappy.h"
#include "gfx.h"

t_cmds	gl_cmds[]=
  {
    {"avance", AVANCE, 7},
    {"droite", DROITE, 7},
    {"gauche", GAUCHE, 7},
    {"voir", VOIR, 7},
    {"inventaire", INVENTAIRE, 1},
    {"prend", PREND, 7},
    {"pose", POSE, 7},
    {"expulse", EXPULSE, 7},
    {"broadcast", BROADCAST, 7},
    {"incantation", INCANTATION, 300},
    {"fork", FORK, 42},
    {"connect_nbr", CONNECT_NBR, 0},
  };

int		handle_commands(t_ctrl *c, t_jm_list *cli, char *s)
{
  unsigned int	i;
  char		*p;

  i = 0;
  (void)c;
  while (i < sizeof(gl_cmds) / sizeof(*gl_cmds))
    {
      if (!strncmp(gl_cmds[i].cmd, s, strlen(gl_cmds[i].cmd)))
  	{
  	  if ((p = strdup(s + strlen(gl_cmds[i].cmd))) == NULL)
  	    return (-1);
	  printf(MAGENTA"From player #%d: '%s'"END,
		 ((t_player *)((t_handler *)cli->data)->p)->id, gl_cmds[i].cmd);
	  return (push_event(&((t_player *)((t_handler *)cli->data)->p)->e,
			     gl_cmds[i].ev, p, (double)gl_cmds[i].time));
  	}
      ++i;
    }
  jm_writeln(cli, "ko");
  return (0);
}
