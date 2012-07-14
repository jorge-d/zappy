/*
** commands.c for zappy in /home/rodrig_d/rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Wed Jun 15 16:18:26 2011 jose rodrigues
** Last update Wed Jun 15 19:32:33 2011 jose rodrigues
*/

#ifndef		COMMANDS_H_
# define	COMMANDS_H_

# include "zappy.h"

enum e_event;

typedef struct	s_cmds
{
  char		*cmd;
  enum e_event	ev;
  int		time;
}		t_cmds;

#endif		/* !COMMANDS_H_ */
