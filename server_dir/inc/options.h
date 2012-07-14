/*
** options.h for zappy in /home/rodrig_d/rendu/c/zappy/server
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Mon Jun 13 16:49:49 2011 jose rodrigues
** Last update Wed Jun 15 15:49:47 2011 jose rodrigues
*/

#ifndef		OPTIONS_H_
# define	OPTIONS_H_

#include "zappy.h"

typedef struct	s_opts
{
  int		port;
  int		map_x;
  int		map_y;
  t_team	*teams;
  int		auth_clients;
  int		time;
}		t_opts;

typedef struct	s_funcs
{
  char		opt;
  int		(*fct)(int ac, char **av, int i, t_opts *opts);
}		t_funcs;

t_opts		*get_opts(int ac, char **av);
char		*get_opt_value(int ac, char **av, int i);
int		opt_port(int ac, char **av, int i, t_opts *op);
int		opt_time(int ac, char **av, int i, t_opts *op);
int		opt_teams(int ac, char **av, int i, t_opts *op);
int		opt_map_y(int ac, char **av, int i, t_opts *op);
int		opt_map_x(int ac, char **av, int i, t_opts *op);
int		opt_auth_clients(int ac, char **av, int i, t_opts *op);
void		free_options(t_opts *o);

#endif		/* !OPTIONS_H_ */
