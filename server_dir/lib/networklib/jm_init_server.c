/*
** jm_connect.c for Network in /home/jorge_d/svn/zappy/networklib
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Fri Jun 10 21:27:23 2011 dimitri jorge
** Last update Tue Jul  5 12:26:26 2011 dimitri jorge
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "jm_network.h"

static int	_get_port(t_jm_sock *s)
{
  socklen_t	addrlen;

  addrlen = sizeof(addrlen);
  if ((ntohs(s->bind.sin_port) == 0))
    {
      if (getsockname(s->socket, (struct sockaddr *)&s->bind, &addrlen) != -1)
        {
          s->port = ntohs(s->bind.sin_port);
          return (1);
        }
      else
	perror("getsockname");
      return (0);
    }
  return (1);
}

static t_jm_sock	*_create_server_socket(int p, int q)
{
  t_jm_sock		*s;
  int			tmp;

  tmp = 1;
  if ((s = malloc(sizeof(*s))) && (s->proto = getprotobyname("TCP")) &&
      (s->socket = socket(PF_INET, SOCK_STREAM, s->proto->p_proto)) != -1)
    {
      s->port = p;
      setsockopt(s->socket, SOL_SOCKET, SO_REUSEADDR, &tmp, sizeof(tmp));
      s->bind.sin_family = AF_INET;
      s->bind.sin_port = htons(s->port);
      s->bind.sin_addr.s_addr = htons(INADDR_ANY);
      if (bind(s->socket, (struct sockaddr *)&s->bind, sizeof(s->bind)) != -1
	  && listen(s->socket, q) != -1 && _get_port(s) == 1)
	return s;
      if (close(s->socket) == -1)
	perror("close");
    }
  else
    perror("jm_init_server");
  free(s);
  return (NULL);
}

int		jm_init_server(t_jm_list **begin, int p, int q)
{
  t_jm_sock	*s;

  if ((s = _create_server_socket(p, q)))
    {
      if (jm_push_fd(begin, s, s->socket, SERVER))
	return (1);
      jm_free_socket(s);
    }
  return (0);
}
