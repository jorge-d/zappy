/*
** jm_init_client.c for network in /home/jorge_d/svn/zappy/networklib
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Sat Jun 11 10:33:36 2011 dimitri jorge
** Last update Thu Jun 23 17:22:35 2011 dimitri jorge
*/

#include <string.h>
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
      if (getsockname(s->socket, (struct sockaddr*)&s->bind, &addrlen) != -1)
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

static t_jm_sock	*_connect_server_socket(char *host, int p)
{
  t_jm_sock		*s;
  struct hostent	*h;

  if ((s = calloc(1, sizeof(*s))) && (s->proto = getprotobyname("TCP")) &&
      (s->socket = socket(PF_INET, SOCK_STREAM, s->proto->p_proto)) != -1)
    {
      if ((h = gethostbyname(host)))
	{
	  s->port = p;
          s->bind.sin_family = AF_INET;
          s->bind.sin_port = htons(s->port);
	  bcopy(h->h_addr, &s->bind.sin_addr, sizeof(s->bind.sin_addr));
	  if (connect(s->socket, (struct sockaddr *)&s->bind,
		      sizeof(s->bind)) != -1 && _get_port(s))
	    return (s);
	}
      if (close(s->socket) == -1)
	perror("close");
    }
  free(s);
  return (NULL);
}

int		jm_init_client(t_jm_list **begin, char *host, int p)
{
  t_jm_sock	*s;

  if ((s = _connect_server_socket(host, p)))
    {
      if (jm_push_fd(begin, s, s->socket, RDWR))
	return (1);
      jm_free_socket(s);
    }
  return (0);
}
