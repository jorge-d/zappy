/*
** zappy.h for zappy in /home/rodrig_d/rendu/c/zappy/server
** 
** Made by jose rodrigues
** Login   <rodrig_d@epitech.net>
** 
** Started on  Mon Jun 13 16:29:18 2011 jose rodrigues
** Last update Sun Jul 10 20:58:15 2011 jose rodrigues
*/

#ifndef		ZAPPY_H_
# define	ZAPPY_H_

# include "jm_network.h"
# include "event.h"
# include "color.h"

# define getmapx(c) (c->options->map_x)
# define getmapy(c) (c->options->map_y)
# define getRealX(c, x) (get_real_map_coord(x, c->options->map_x))
# define getRealY(c, y) (get_real_map_coord(y, c->options->map_y))

# define getframe(c, x, y) \
  (c->map[getRealY(c, y) * getmapx(c) + getRealX(c, x)])

typedef enum	e_dir
  {
    UP,
    LEFT,
    DOWN,
    RIGHT
  }		e_dir;

typedef struct	s_inventory
{
  int		linemate;
  int		deraumere;
  int		sibur;
  int		mendiane;
  int		phiras;
  int		thystame;
}		t_inventory;

typedef struct s_team t_team;

typedef struct		s_player
{
  int			id;
  int			food;
  int			lvl;
  int			x;
  int			y;
  enum e_dir		d;
  t_jm_list		*fd;
  t_inventory		inventory;
  t_team		*t;
  t_event		*e;
  struct s_player	*next;
  struct s_player	*prev;
}			t_player;

struct		s_team
{
  char		*name;
  int		nb_fork;
  int		nblvlmax;
  t_player	*players;
  struct s_team	*next;
  struct s_team	*prev;
};

typedef struct		s_closable
{
  t_jm_list		*p;
  struct s_closable	*next;
}			t_closable;

typedef enum	e_elem
  {
    NOURRITURE,
    LINEMATE,
    DERAUMERE,
    SIBUR,
    MENDIANE,
    PHIRAS,
    THYSTAME,
    PLAYER,
    ALL
  }		e_elem;

typedef struct	s_pp
{
  char		*name;
  enum e_elem	elem;
  off_t		off;
}		t_pp;

typedef struct		s_frame
{
  enum e_elem		type;
  void			*p;
  struct s_frame	*next;
  struct s_frame	*prev;
}			t_frame;

typedef struct		s_eclode
{
  int			id_parent;
  int			id;
  int			x;
  int			y;
  t_team		*t;
  double		duration;
  struct timeval	start_time;
  struct s_eclode	*next;
  struct s_eclode	*prev;
}			t_eclode;

struct s_opts;
typedef struct	s_ctrl
{
  int			id_player;
  struct s_opts		*options;
  int			flag;
  t_team		*teams;
  t_jm_list		*l;
  t_closable		*to_close;
  t_frame		**map;
  t_life		*life;
  t_eclode		*eggs;
  struct timeval	delay;
}		t_ctrl;

typedef enum	e_client
  {
    UNDEFINED,
    GFX,
    IA
  }		e_client;

typedef struct	s_handler
{
  enum e_client	t;
  void		*p;
  int		(*handler)(t_ctrl *c, t_jm_list *cli, char *s);
}		t_handler;

void		get_commands(t_ctrl *c, t_jm_list *tmp);
t_ctrl		*init_server(int ac, char **av);
int		start_zappy(t_ctrl *c);
int		handle_type(t_ctrl *c, t_jm_list *cli, char *s);
int		handle_commands(t_ctrl *c, t_jm_list *cli, char *s);
int		handle_gfx(t_ctrl *c, t_jm_list *cli, char *s);
int		player_list_size(t_team *t);
void		handle_closable(t_ctrl *c);
int		push_closable(t_closable **begin, t_jm_list *t);
t_player	*create_player(t_ctrl *, t_team *, t_jm_list *, int);

t_player	*get_player_from_id(t_ctrl *c, int id);
void		set_elem_on_map(t_ctrl *c, t_frame *node, int x, int y);
void		unset_elem_from_map(t_ctrl *c, t_frame *node, int x, int y);
int		push_elem_on_map(t_ctrl *c, void *p, int x, int y, e_elem t);
void		print_map(t_ctrl *c);
t_frame		*get_elem_from_map(t_ctrl*c, int x, int y, e_elem e);
int		get_real_map_coord(int c, int max);

void		remove_player(t_ctrl *c, t_player *p);
void		handle_eclosion(t_ctrl *c, t_eclode *tmp);
void		free_control(t_ctrl *c);
void		reset_player_into_map(t_ctrl *c, t_player *p, int x, int y);
int		attribute_player(t_ctrl *c, t_jm_list *l, t_team *t);
void		free_closable(t_closable *t);

void		get_nb_elems(t_ctrl *c, int t[ALL]);
int		generate_elems(t_ctrl *c);
void		dispatch_elems(t_ctrl *c, int x, int y);

#endif		/* !ZAPPY_H_ */
