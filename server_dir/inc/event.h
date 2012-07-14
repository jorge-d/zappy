/*
** event.h for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 15 19:22:07 2011 dimitri jorge
** Last update Tue Jul  5 12:57:03 2011 dimitri jorge
*/

#ifndef		EVENT__H_
# define	EVENT__H_

typedef struct	s_incant
{
  int		lvl;
  int		players;
  int		linemate;
  int		deraumere;
  int		sibur;
  int		mendiane;
  int		phiras;
  int		thystame;
}		t_incant;

typedef enum	e_event
  {
    AVANCE,
    DROITE,
    GAUCHE,
    VOIR,
    INVENTAIRE,
    PREND,
    POSE,
    EXPULSE,
    BROADCAST,
    INCANTATION,
    FORK,
    CONNECT_NBR
  }		e_event;

typedef struct		s_event
{
  e_event		type;
  char			*param;
  double		duration;
  struct timeval	start_time;
  struct s_event	*next;
}			t_event;

struct s_ctrl;
struct s_player;

typedef struct	s_ev_funcs
{
  e_event	ev;
  int		(*fct)(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
}		t_ev_funcs;

struct s_player;
typedef struct		s_life
{
  struct timeval	start_time;
  struct s_player	*p;
  struct s_life		*next;
  struct s_life		*prev;
}			t_life;

typedef struct	s_op_coord
{
  int		op_x;
  int		op_y;
}		t_op_coord;

typedef struct	s_turn
{
  int		val;
  int		x;
  int		y;
}		t_turn;

int	get_frame_number(struct s_ctrl *c, struct s_player *p, int x, int y);
int	push_event(t_event **begin, e_event t, char *s, double);
void	free_events(t_event *e);
int	set_time_in_node(t_event *n, double f);
void	handle_events(struct s_ctrl *c);
void	reset_time_in_node(t_event *n, struct timeval *e);

void	remove_life_node(struct s_ctrl *c, struct s_player *p);
int	push_life(struct s_ctrl *c, struct s_player *p);

int	avance(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	droite(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	gauche(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	voir(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	inventaire(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	prend(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	pose(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	expulse(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	broadcast(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	incantation(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	fork_z(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);
int	connect_nbr(struct s_ctrl *c, t_jm_list *cli, struct s_player *p);

enum e_elem;

int	get_nb_players(struct s_ctrl *c, int x, int y, int lvl);
int	get_nb_object(struct s_ctrl *c, int x, int y, enum e_elem e);
void	elevate_players(struct s_ctrl *c, int x, int y, int lvl);

int	reset_lifetime(t_life *n, double d);
void	handle_life(struct s_ctrl *c, t_life *tmp);
int	can_elevate(struct s_ctrl *c, struct s_player *p);

#endif
