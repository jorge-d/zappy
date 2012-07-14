/*
** gfx.h for zappy in /home/jorge_d/svn/zappy/server_dir
** 
** Made by dimitri jorge
** Login   <jorge_d@epitech.net>
** 
** Started on  Wed Jun 22 17:49:11 2011 dimitri jorge
** Last update Mon Jun 27 13:26:42 2011 jose rodrigues
*/

#ifndef __GFX_H__
# define __GFX_H__

#include "zappy.h"

typedef struct	s_gfp
{
  char		*cmd;
  void		(*p)(t_ctrl *, t_jm_list *, char *);
}		t_gfp;

/*
** functions_1.c
*/

void	msz(t_ctrl *c, t_jm_list *l);
void	bct(t_ctrl *c, t_jm_list *l, int x, int y);
void	mct(t_ctrl *c, t_jm_list *l);
void	tna(t_ctrl *c, t_jm_list *l);
void	pnw(t_jm_list *l, t_player *p);

/*
** functions_2.c
*/

void	ppo(t_ctrl *c, t_jm_list *l, int id);
void	plv(t_ctrl *c, t_jm_list *l, int id);
void	pin(t_ctrl *c, t_jm_list *l, int id);
void	pex(t_jm_list *l, int id);
void	pbc(t_jm_list *l, int id, char *s);

/*
** functions_3.c
*/

void	plc(t_jm_list *l, t_player *p, int *ids);
void	ple(t_jm_list *l, t_player *p, char res);
void	pfk(t_jm_list *l, t_player *p);
void	pdr(t_jm_list *l, t_player *p, e_elem t);
void	pgt(t_jm_list *l, t_player *p, e_elem t);

/*
** functions_4.c
*/

void	pdi(t_jm_list *l, t_player *p);
void	enw(t_jm_list *l, int idp, t_eclode *o);
void	eht(t_jm_list *l, t_eclode *o);
void	ebo(t_jm_list *l, t_player *p);
void	edi(t_jm_list *l, t_player *p);

/*
** functions_5.c
*/

void	sgt(t_ctrl *c, t_jm_list *l);
void	sst(t_ctrl *c, t_jm_list *l, int t);
void	seg(t_jm_list *l, char *n);
void	smg(t_jm_list *l, char *n);

/*
** player_actions_1.c
*/

void	gfx_player_join(t_ctrl *c, t_player *p);
void	gfx_player_expulse(t_ctrl *c, t_player *p, int *ids);
void	gfx_player_broadcast(t_ctrl *c, t_player *p, char *s);
void	gfx_player_begin_incantation(t_ctrl *c, t_player *p);

/*
** player_action_2.c
*/

void	gfx_player_end_incantation(t_ctrl *c, t_player *p, int res);
void	gfx_player_has_fork(t_ctrl *c, t_player *p);
void	gfx_player_throws_object(t_ctrl *c, t_player *p, enum e_elem e);
void	gfx_player_takes_object(t_ctrl *c, t_player *p, enum e_elem e);
void	gfx_player_is_dead(t_ctrl *c, t_player *p);

/*
** player_action_3.c
*/

void	gfx_player_fork_end(t_ctrl *c, t_player *p, t_eclode *o);
void	gfx_egg_hatched(t_ctrl *c, t_eclode *o);
void	gfx_player_connect_egg(t_ctrl *c, t_player *p);
void	gfx_egg_died(t_ctrl *c, t_player *p);
void	gfx_end_of_game(t_ctrl *c, char *s);

/*
** player_action_4.c
*/

void	gfx_player_moves(t_ctrl *c, t_player *p);

/*
** list_eggs_and_players.c
*/

void	list_eggs_and_players(t_ctrl *c, t_jm_list *l);

/*
** server_messages.c
*/

void	gfx_server_msg(t_ctrl *c, char *msg);
void	suc(t_jm_list *l);
void	sbp(t_jm_list *l);
void	gfx_send_frame_content(t_ctrl *c, int x, int y);

/*
** handle_protocol.c
*/
void	gfx_get_mapsize(t_ctrl *c, t_jm_list *l, char *s);
void	gfx_get_frame(t_ctrl *c, t_jm_list *l, char *s);
void	gfx_get_all_frames(t_ctrl *c, t_jm_list *l, char *s);
void	gfx_get_teamnames(t_ctrl *c, t_jm_list *l, char *s);
void	gfx_get_player_position(t_ctrl *c, t_jm_list *l, char *s);
void	gfx_get_player_level(t_ctrl *c, t_jm_list *l, char *s);
void	gfx_get_player_inventory(t_ctrl *c, t_jm_list *l, char *s);
void	gfx_get_time_unit(t_ctrl *c, t_jm_list *l, char *s);
void	gfx_set_time_unit(t_ctrl *c, t_jm_list *l, char *s);

#endif
