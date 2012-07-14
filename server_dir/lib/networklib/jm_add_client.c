/*
** jm_add_client.c for network in /home/jorge_d/svn/zappy/networklib
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Mon Jun 13 12:32:02 2011 dimitri jorge
** Last update Thu Jul  7 16:05:19 2011 dimitri jorge
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "jm_network.h"
#include "color.h"

void		jm_add_client(t_jm_list **begin, t_jm_list *tmp)
{
  t_jm_sock	*s;
  socklen_t     addrlen;

  if ((s = calloc(1, sizeof(*s))))
    {
      addrlen = sizeof(s->bind);
      if ((s->socket = accept(tmp->fd,
			      (struct sockaddr *)&s->bind, &addrlen)) != -1)
        {
	  if (!jm_push_fd(begin, s, s->socket, RDWR))
	    jm_free_socket(s);
	  else
	    printf(BLUE"New connection from <%s>!"END,
		   inet_ntoa(s->bind.sin_addr));
        }
      else
	perror("Accept");
    }
  else
    perror("calloc");
}
