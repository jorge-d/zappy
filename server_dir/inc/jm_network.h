/*
** jm_network.h for zappy in /home/rodrig_d//rendu/c/zappy/server_dir
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Mon Jun 27 13:27:17 2011 jose rodrigues
** Last update Thu Jul  7 15:20:51 2011 dimitri jorge
*/

#ifndef __JM_NETWORK_H__
# define __JM_NETWORK_H__

#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

# define BUFFSIZE 8192
# define RDBLOCK 4096

# define jm_write(a, b) jm_push_write(a, b, 0)
# define jm_writeln(a, b) jm_push_write(a, b, 1)

typedef enum	e_jm_type
  {
    SERVER,
    READ,
    WRITE,
    RDWR
  }		jm_type;

typedef struct		s_jm_sock
{
  int			socket;
  int			port;
  struct sockaddr_in	bind;
  struct protoent	*proto;
}			t_jm_sock;

typedef struct		s_circular
{
  char			buff[BUFFSIZE];
  int			rdidx;
  int			wridx;
}			t_circular;

typedef struct		s_writelist
{
  char			buff[BUFFSIZE + 1];
  struct s_writelist	*next;
}			t_writelist;

typedef struct		s_jm_list
{
  int			fd;
  int			flag;
  jm_type		type;
  t_jm_sock		*s;
  t_circular		buffread;
  t_writelist		*buffwrite;
  void			*data;
  struct s_jm_list	*next;
  struct s_jm_list	*prev;
}			t_jm_list;

int jm_init_server(t_jm_list **, int, int);
int jm_push_fd(t_jm_list **, t_jm_sock *, int, jm_type);
void jm_push_write(t_jm_list *, char *, int);
void jm_free_socket(t_jm_sock *);
void jm_free_list(t_jm_list *);
void jm_select(t_jm_list **, struct timeval *);
int jm_init_client(t_jm_list **, char *, int);
char *jm_get_msg(t_jm_list *);

void jm_handle_write(t_jm_list *);
void jm_handle_read(t_jm_list *);
void jm_add_client(t_jm_list **, t_jm_list *);
void jm_remove_from_list(t_jm_list **, t_jm_list *);
void jm_free_writebuff(t_writelist *);

#endif
