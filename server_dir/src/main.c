/*
** main.c for zappy in /home/rodrig_d/rendu/c/zappy/server
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Mon Jun 13 16:26:16 2011 jose rodrigues
** Last update Thu Jul  7 16:04:31 2011 dimitri jorge
*/

#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include "zappy.h"
#include "options.h"

int		*gl_flag;

static void	_handle_sign(int s)
{
  (void)s;
  *gl_flag = 0;
}

int		main(int ac, char **av)
{
  t_ctrl	*c;

  if (!(c = init_server(ac, av)))
    return (EXIT_FAILURE);
  gl_flag = &c->flag;
  if ((signal(SIGINT, _handle_sign)) == SIG_ERR)
    perror("signal");
  start_zappy(c);
  free_control(c);
  printf(RED"Server shutting down"END);
  return (0);
}
